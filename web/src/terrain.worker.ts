import { unzipSync } from 'fflate';
import {
  MISSING_LEVEL,
  type BuildRequest,
  type Projection,
  type TileInfo,
  type WorkerRequest,
  type WorkerResponse,
} from './shared';

const VOID = -32768;
const CHUNK = 128;
const M_PER_DEG_LAT = 110574;
const M_PER_DEG_LON_EQUATOR = 111320;

interface RawTile {
  info: TileInfo;
  samples: number;
  data: Int16Array;
}

interface Grid {
  width: number;
  height: number;
  cellSize: number;
  heights: Float32Array;
}

let tiles: RawTile[] = [];
let projection: Projection | null = null;
const gridCache = new Map<number, Grid>();
let latestJob = 0;

function post(msg: WorkerResponse, transfer: Transferable[] = []): void {
  (self as unknown as { postMessage(m: unknown, t: Transferable[]): void }).postMessage(msg, transfer);
}

const nextTick = () => new Promise<void>((resolve) => setTimeout(resolve, 0));

self.onmessage = (e: MessageEvent<WorkerRequest>) => {
  const msg = e.data;
  const run = msg.type === 'load' ? load(msg.tiles) : build(msg);
  run.catch((err: unknown) => post({ type: 'error', message: err instanceof Error ? err.message : String(err) }));
};

async function mapLimit<T, R>(items: T[], limit: number, fn: (item: T) => Promise<R>): Promise<R[]> {
  const out: R[] = new Array(items.length);
  let next = 0;
  const runners = Array.from({ length: Math.min(limit, items.length) }, async () => {
    while (next < items.length) {
      const i = next++;
      out[i] = await fn(items[i]);
    }
  });
  await Promise.all(runners);
  return out;
}

function decodeHgt(bytes: Uint8Array, name: string): { samples: number; data: Int16Array } {
  const samples = Math.round(Math.sqrt(bytes.length / 2));
  if (samples * samples * 2 !== bytes.length) throw new Error(`${name}: not a square .hgt grid (${bytes.length} bytes)`);
  const view = new DataView(bytes.buffer, bytes.byteOffset, bytes.byteLength);
  const data = new Int16Array(samples * samples);
  for (let k = 0; k < data.length; k++) data[k] = view.getInt16(k * 2, false);
  return { samples, data };
}

async function load(infos: TileInfo[]): Promise<void> {
  if (infos.length === 0) throw new Error('No SRTM tiles found');
  let loaded = 0;
  post({ type: 'loadProgress', loaded, total: infos.length });

  tiles = await mapLimit(infos, 6, async (info) => {
    const res = await fetch(info.url);
    if (!res.ok) throw new Error(`${info.name}: HTTP ${res.status}`);
    let bytes = new Uint8Array(await res.arrayBuffer());
    if (/\.zip$/i.test(info.url) || (bytes[0] === 0x50 && bytes[1] === 0x4b)) {
      const files = unzipSync(bytes, { filter: (f) => f.name.toLowerCase().endsWith('.hgt') });
      const entry = Object.values(files)[0];
      if (!entry) throw new Error(`${info.name}: no .hgt file in archive`);
      bytes = entry;
    }
    const tile = { info, ...decodeHgt(bytes, info.name) };
    post({ type: 'loadProgress', loaded: ++loaded, total: infos.length });
    return tile;
  });

  let latMin = Infinity, latMax = -Infinity, lonMin = Infinity, lonMax = -Infinity;
  let minElevation = Infinity, maxElevation = -Infinity;
  for (const t of tiles) {
    latMin = Math.min(latMin, t.info.lat);
    latMax = Math.max(latMax, t.info.lat + 1);
    lonMin = Math.min(lonMin, t.info.lon);
    lonMax = Math.max(lonMax, t.info.lon + 1);
    for (const h of t.data) {
      if (h === VOID) continue;
      if (h < minElevation) minElevation = h;
      if (h > maxElevation) maxElevation = h;
    }
  }

  const lat0 = (latMin + latMax) / 2;
  const lon0 = (lonMin + lonMax) / 2;
  const kx = M_PER_DEG_LON_EQUATOR * Math.cos((lat0 * Math.PI) / 180);
  const kz = M_PER_DEG_LAT;
  projection = {
    lat0, lon0, kx, kz,
    xMin: (lonMin - lon0) * kx,
    xMax: (lonMax - lon0) * kx,
    zMin: (lat0 - latMax) * kz,
    zMax: (lat0 - latMin) * kz,
  };
  gridCache.clear();
  post({ type: 'loaded', projection, minElevation, maxElevation, tileCount: tiles.length });
}

/** Box-filters every raw SRTM sample into a square metric grid of `cellSize` metres; NaN marks cells without data. */
function resample(cellSize: number): Grid {
  const cached = gridCache.get(cellSize);
  if (cached) return cached;
  const p = projection!;
  const width = Math.ceil((p.xMax - p.xMin) / cellSize);
  const height = Math.ceil((p.zMax - p.zMin) / cellSize);
  const sum = new Float64Array(width * height);
  const count = new Uint32Array(width * height);

  for (const t of tiles) {
    const n = t.samples;
    const step = 1 / (n - 1);
    const colCell = new Int32Array(n);
    const rowCell = new Int32Array(n);
    for (let c = 0; c < n; c++) {
      const x = (t.info.lon + c * step - p.lon0) * p.kx;
      colCell[c] = Math.min(width - 1, Math.max(0, Math.floor((x - p.xMin) / cellSize)));
    }
    for (let r = 0; r < n; r++) {
      const z = (p.lat0 - (t.info.lat + 1 - r * step)) * p.kz;
      rowCell[r] = Math.min(height - 1, Math.max(0, Math.floor((z - p.zMin) / cellSize)));
    }
    for (let r = 0; r < n; r++) {
      const rowBase = rowCell[r] * width;
      const src = r * n;
      for (let c = 0; c < n; c++) {
        const h = t.data[src + c];
        if (h === VOID) continue;
        const k = rowBase + colCell[c];
        sum[k] += h;
        count[k]++;
      }
    }
  }

  const heights = new Float32Array(width * height);
  for (let k = 0; k < heights.length; k++) heights[k] = count[k] ? sum[k] / count[k] : NaN;

  const grid = { width, height, cellSize, heights };
  gridCache.set(cellSize, grid);
  if (gridCache.size > 3) gridCache.delete(gridCache.keys().next().value!);
  return grid;
}

class MeshBuilder {
  positions = new Float32Array(3 * 4096);
  normals = new Int8Array(3 * 4096);
  indices = new Uint32Array(6 * 1024);
  vertexCount = 0;
  indexCount = 0;

  private reserve(vertices: number, indices: number): void {
    if ((this.vertexCount + vertices) * 3 > this.positions.length) {
      const size = Math.max(this.positions.length * 2, (this.vertexCount + vertices) * 3);
      const pos = new Float32Array(size);
      pos.set(this.positions);
      this.positions = pos;
      const nrm = new Int8Array(size);
      nrm.set(this.normals);
      this.normals = nrm;
    }
    if (this.indexCount + indices > this.indices.length) {
      const idx = new Uint32Array(Math.max(this.indices.length * 2, this.indexCount + indices));
      idx.set(this.indices);
      this.indices = idx;
    }
  }

  vertex(x: number, y: number, z: number, nx: number, ny: number, nz: number): number {
    this.reserve(1, 0);
    const o = this.vertexCount * 3;
    this.positions[o] = x;
    this.positions[o + 1] = y;
    this.positions[o + 2] = z;
    this.normals[o] = Math.round(nx * 127);
    this.normals[o + 1] = Math.round(ny * 127);
    this.normals[o + 2] = Math.round(nz * 127);
    return this.vertexCount++;
  }

  triangle(a: number, b: number, c: number): void {
    this.reserve(0, 3);
    this.indices[this.indexCount++] = a;
    this.indices[this.indexCount++] = b;
    this.indices[this.indexCount++] = c;
  }

  /** Corners must be counter-clockwise when viewed from the side the normal points to. */
  quad(c: number[], n: [number, number, number]): void {
    const a = this.vertex(c[0], c[1], c[2], ...n);
    const b = this.vertex(c[3], c[4], c[5], ...n);
    const d = this.vertex(c[6], c[7], c[8], ...n);
    const e = this.vertex(c[9], c[10], c[11], ...n);
    this.triangle(a, b, d);
    this.triangle(a, d, e);
  }

  result() {
    return {
      positions: this.positions.slice(0, this.vertexCount * 3),
      normals: this.normals.slice(0, this.vertexCount * 3),
      indices: this.indices.slice(0, this.indexCount),
    };
  }
}

/** Quantises exaggerated heights into cube-sized levels so rendered blocks are cubes. */
function computeLevels(grid: Grid, exaggeration: number): { levels: Int32Array; baseLevel: number } {
  const levels = new Int32Array(grid.heights.length);
  let min = Infinity;
  for (let k = 0; k < levels.length; k++) {
    const h = grid.heights[k];
    if (Number.isNaN(h)) {
      levels[k] = MISSING_LEVEL;
    } else {
      levels[k] = Math.round((h * exaggeration) / grid.cellSize);
      if (levels[k] < min) min = levels[k];
    }
  }
  return { levels, baseLevel: (Number.isFinite(min) ? min : 0) - 2 };
}

function voxelChunk(
  grid: Grid, levels: Int32Array, baseLevel: number,
  i0: number, j0: number, i1: number, j1: number,
): MeshBuilder {
  const { width: W, height: H } = grid;
  const p = projection!;
  const km = grid.cellSize / 1000;
  const X = (i: number) => p.xMin / 1000 + i * km;
  const Z = (j: number) => p.zMin / 1000 + j * km;
  const Y = (level: number) => level * km;
  const levelAt = (i: number, j: number) => levels[j * W + i];
  const neighbour = (i: number, j: number) => {
    if (i < 0 || j < 0 || i >= W || j >= H) return baseLevel;
    const l = levels[j * W + i];
    return l === MISSING_LEVEL ? baseLevel : l;
  };
  const b = new MeshBuilder();
  const cw = i1 - i0;
  const ch = j1 - j0;

  // Greedy-merge top faces of equal level into rectangles.
  const used = new Uint8Array(cw * ch);
  for (let j = 0; j < ch; j++) {
    for (let i = 0; i < cw; i++) {
      if (used[j * cw + i]) continue;
      const lv = levelAt(i0 + i, j0 + j);
      if (lv === MISSING_LEVEL) continue;
      let w = 1;
      while (i + w < cw && !used[j * cw + i + w] && levelAt(i0 + i + w, j0 + j) === lv) w++;
      let h = 1;
      grow: while (j + h < ch) {
        for (let k = 0; k < w; k++) {
          if (used[(j + h) * cw + i + k] || levelAt(i0 + i + k, j0 + j + h) !== lv) break grow;
        }
        h++;
      }
      for (let jj = 0; jj < h; jj++) used.fill(1, (j + jj) * cw + i, (j + jj) * cw + i + w);
      const x0 = X(i0 + i), x1 = X(i0 + i + w), z0 = Z(j0 + j), z1 = Z(j0 + j + h), y = Y(lv);
      b.quad([x0, y, z1, x1, y, z1, x1, y, z0, x0, y, z0], [0, 1, 0]);
    }
  }

  // Side walls: one quad per run of cells sharing the same (level, neighbour level) pair.
  const runs = (
    outer: number, inner: number,
    cell: (o: number, n: number) => [number, number],
    di: number, dj: number,
    emit: (o: number, nStart: number, nEnd: number, top: number, bottom: number) => void,
  ) => {
    for (let o = 0; o < outer; o++) {
      let n = 0;
      while (n < inner) {
        const [ci, cj] = cell(o, n);
        const lv = levelAt(ci, cj);
        const nl = neighbour(ci + di, cj + dj);
        if (lv === MISSING_LEVEL || lv <= nl) { n++; continue; }
        let end = n + 1;
        while (end < inner) {
          const [ei, ej] = cell(o, end);
          if (levelAt(ei, ej) !== lv || neighbour(ei + di, ej + dj) !== nl) break;
          end++;
        }
        emit(o, n, end, Y(lv), Y(nl));
        n = end;
      }
    }
  };

  runs(cw, ch, (o, n) => [i0 + o, j0 + n], 1, 0, (o, s, e, yt, yb) => {
    const x = X(i0 + o + 1), z0 = Z(j0 + s), z1 = Z(j0 + e);
    b.quad([x, yb, z1, x, yb, z0, x, yt, z0, x, yt, z1], [1, 0, 0]);
  });
  runs(cw, ch, (o, n) => [i0 + o, j0 + n], -1, 0, (o, s, e, yt, yb) => {
    const x = X(i0 + o), z0 = Z(j0 + s), z1 = Z(j0 + e);
    b.quad([x, yb, z0, x, yb, z1, x, yt, z1, x, yt, z0], [-1, 0, 0]);
  });
  runs(ch, cw, (o, n) => [i0 + n, j0 + o], 0, 1, (o, s, e, yt, yb) => {
    const z = Z(j0 + o + 1), x0 = X(i0 + s), x1 = X(i0 + e);
    b.quad([x0, yb, z, x1, yb, z, x1, yt, z, x0, yt, z], [0, 0, 1]);
  });
  runs(ch, cw, (o, n) => [i0 + n, j0 + o], 0, -1, (o, s, e, yt, yb) => {
    const z = Z(j0 + o), x0 = X(i0 + s), x1 = X(i0 + e);
    b.quad([x1, yb, z, x0, yb, z, x0, yt, z, x1, yt, z], [0, 0, -1]);
  });

  return b;
}

function smoothChunk(grid: Grid, exaggeration: number, i0: number, j0: number, i1: number, j1: number): MeshBuilder {
  const { width: W, height: H, heights, cellSize } = grid;
  const p = projection!;
  const km = cellSize / 1000;
  const at = (i: number, j: number, fallback: number) => {
    if (i < 0 || j < 0 || i >= W || j >= H) return fallback;
    const h = heights[j * W + i];
    return Number.isNaN(h) ? fallback : h;
  };
  const b = new MeshBuilder();
  const nx = i1 - i0 + 1;
  const nz = j1 - j0 + 1;
  for (let j = j0; j <= j1; j++) {
    for (let i = i0; i <= i1; i++) {
      const h = at(i, j, 0);
      const dx = ((at(i + 1, j, h) - at(i - 1, j, h)) * exaggeration) / (2 * cellSize);
      const dz = ((at(i, j + 1, h) - at(i, j - 1, h)) * exaggeration) / (2 * cellSize);
      const len = Math.hypot(dx, 1, dz);
      b.vertex(
        p.xMin / 1000 + (i + 0.5) * km,
        (h * exaggeration) / 1000,
        p.zMin / 1000 + (j + 0.5) * km,
        -dx / len, 1 / len, -dz / len,
      );
    }
  }
  const valid = (i: number, j: number) => !Number.isNaN(heights[j * W + i]);
  for (let j = 0; j < nz - 1; j++) {
    for (let i = 0; i < nx - 1; i++) {
      const gi = i0 + i, gj = j0 + j;
      if (!valid(gi, gj) || !valid(gi + 1, gj) || !valid(gi, gj + 1) || !valid(gi + 1, gj + 1)) continue;
      const nw = j * nx + i, ne = nw + 1, sw = nw + nx, se = sw + 1;
      b.triangle(sw, se, ne);
      b.triangle(sw, ne, nw);
    }
  }
  return b;
}

async function build(req: BuildRequest): Promise<void> {
  latestJob = req.jobId;
  if (!projection) return;
  const started = performance.now();
  const grid = resample(req.cellSize);
  await nextTick();
  if (req.jobId !== latestJob) return;

  const { width: W, height: H } = grid;
  const voxel = req.mode === 'voxel' ? computeLevels(grid, req.exaggeration) : null;

  const chunks: [number, number, number, number][] = [];
  for (let j0 = 0; j0 < H; j0 += CHUNK) {
    for (let i0 = 0; i0 < W; i0 += CHUNK) {
      if (voxel) {
        chunks.push([i0, j0, Math.min(i0 + CHUNK, W), Math.min(j0 + CHUNK, H)]);
      } else {
        const i1 = Math.min(i0 + CHUNK, W - 1), j1 = Math.min(j0 + CHUNK, H - 1);
        if (i1 > i0 && j1 > j0) chunks.push([i0, j0, i1, j1]);
      }
    }
  }

  post({ type: 'buildStart', jobId: req.jobId, totalChunks: chunks.length });
  const heights = grid.heights.slice();
  const levels = voxel ? voxel.levels.slice() : null;
  post(
    { type: 'grid', jobId: req.jobId, width: W, height: H, cellSize: grid.cellSize, heights, levels, baseLevel: voxel?.baseLevel ?? 0 },
    levels ? [heights.buffer, levels.buffer] : [heights.buffer],
  );

  let triangles = 0;
  let done = 0;
  for (const [i0, j0, i1, j1] of chunks) {
    const b = voxel
      ? voxelChunk(grid, voxel.levels, voxel.baseLevel, i0, j0, i1, j1)
      : smoothChunk(grid, req.exaggeration, i0, j0, i1, j1);
    done++;
    triangles += b.indexCount / 3;
    const { positions, normals, indices } = b.result();
    post(
      { type: 'chunk', jobId: req.jobId, done, positions, normals, indices },
      [positions.buffer, normals.buffer, indices.buffer],
    );
    if (done % 4 === 0) {
      await nextTick();
      if (req.jobId !== latestJob) return;
    }
  }
  post({ type: 'done', jobId: req.jobId, chunks: chunks.length, triangles, ms: performance.now() - started });
}
