import * as THREE from 'three';
import { OrbitControls } from 'three/examples/jsm/controls/OrbitControls.js';
import {
  MISSING_LEVEL,
  parseTileName,
  unproject,
  type Projection,
  type RenderMode,
  type TileInfo,
  type WorkerResponse,
} from './shared';

const tileUrls = import.meta.glob('../../SRTM/*.hgt.zip', { query: '?url', import: 'default', eager: true }) as Record<string, string>;

const $ = <T extends HTMLElement>(id: string) => document.getElementById(id) as T;
const ui = {
  canvas: $<HTMLCanvasElement>('view'),
  status: $('status'),
  statusText: $('status-text'),
  statusBar: $('status-bar'),
  cell: $<HTMLSelectElement>('cell'),
  exag: $<HTMLInputElement>('exag'),
  exagOut: $<HTMLOutputElement>('exag-out'),
  sun: $<HTMLInputElement>('sun'),
  sunOut: $<HTMLOutputElement>('sun-out'),
  grid: $<HTMLInputElement>('grid'),
  stats: $('stats'),
  hover: $('hover'),
};

const SKY = new THREE.Color('#9fb8cc');

// Hypsometric tint (metres → sRGB), converted to linear for the shader.
const PALETTE: [number, string][] = [
  [-50, '#3d6e8f'],
  [0, '#4e7d45'],
  [200, '#6f9650'],
  [400, '#a6b86c'],
  [650, '#d8cb8c'],
  [900, '#c6a06d'],
  [1200, '#a37c58'],
  [1600, '#8c7a6b'],
  [2000, '#b9b4ae'],
  [2400, '#f2f2f2'],
];

function paletteGlsl(): string {
  const v = (c: THREE.Color) => `vec3(${c.r.toFixed(4)}, ${c.g.toFixed(4)}, ${c.b.toFixed(4)})`;
  const cols = PALETTE.map(([, hex]) => new THREE.Color(hex));
  let body = `if (e <= ${PALETTE[0][0].toFixed(1)}) return ${v(cols[0])};\n`;
  for (let k = 1; k < PALETTE.length; k++) {
    const [e0] = PALETTE[k - 1];
    const [e1] = PALETTE[k];
    body += `if (e <= ${e1.toFixed(1)}) return mix(${v(cols[k - 1])}, ${v(cols[k])}, (e - ${e0.toFixed(1)}) / ${(e1 - e0).toFixed(1)});\n`;
  }
  return `vec3 hypso(float e) {\n${body}return ${v(cols[cols.length - 1])};\n}`;
}

function createTerrainMaterial() {
  const uniforms = {
    uExag: { value: 4 },
    uCell: { value: 0.5 },
    uOrigin: { value: new THREE.Vector3() },
    uGrid: { value: 1 },
    uVoxel: { value: 1 },
    uHeights: { value: null as THREE.DataTexture | null },
  };
  const material = new THREE.MeshLambertMaterial({ color: 0xffffff });
  material.onBeforeCompile = (shader) => {
    Object.assign(shader.uniforms, uniforms);
    shader.vertexShader = shader.vertexShader
      .replace('#include <common>', '#include <common>\nvarying vec3 vWorldPos;\nvarying vec3 vObjNormal;')
      .replace(
        '#include <project_vertex>',
        '#include <project_vertex>\nvWorldPos = (modelMatrix * vec4(transformed, 1.0)).xyz;\nvObjNormal = normal;',
      );
    shader.fragmentShader = shader.fragmentShader
      .replace(
        '#include <common>',
        `#include <common>
varying vec3 vWorldPos;
varying vec3 vObjNormal;
uniform float uExag;
uniform float uCell;
uniform vec3 uOrigin;
uniform float uGrid;
uniform float uVoxel;
uniform highp sampler2D uHeights;
${paletteGlsl()}`,
      )
      .replace(
        'vec4 diffuseColor = vec4( diffuse, opacity );',
        `float elevation = vWorldPos.y * 1000.0 / uExag;
if (uVoxel > 0.5) {
  // Tint voxels by the cell's real mean height, not its rounded block level; walls belong to the cell behind them.
  vec2 cellPos = (vWorldPos.xz - uOrigin.xz) / uCell - vObjNormal.xz * 0.25;
  ivec2 size = textureSize(uHeights, 0);
  ivec2 cell = clamp(ivec2(floor(cellPos)), ivec2(0), size - 1);
  elevation = texelFetch(uHeights, cell, 0).r;
}
vec3 tint = hypso(elevation);
if (uGrid > 0.5) {
  vec3 p = (vWorldPos - uOrigin) / uCell;
  vec3 fw = max(fwidth(p), vec3(1e-4));
  vec3 d = abs(fract(p - 0.5) - 0.5) / fw;
  vec3 n = abs(normalize(vObjNormal));
  float dist = 1e3;
  if (n.x < 0.5) dist = min(dist, d.x);
  if (n.y < 0.5) dist = min(dist, d.y);
  if (n.z < 0.5) dist = min(dist, d.z);
  float fade = 1.0 - smoothstep(0.15, 0.45, max(max(fw.x, fw.y), fw.z));
  tint *= 1.0 - 0.28 * (1.0 - clamp(dist - 0.5, 0.0, 1.0)) * fade;
}
vec4 diffuseColor = vec4( diffuse * tint, opacity );`,
      );
  };
  return { material, uniforms };
}

// --- Scene ---------------------------------------------------------------

const renderer = new THREE.WebGLRenderer({ canvas: ui.canvas, antialias: true });
renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
renderer.setSize(window.innerWidth, window.innerHeight);

const scene = new THREE.Scene();
scene.background = SKY;
scene.fog = new THREE.Fog(SKY, 400, 1600);

const camera = new THREE.PerspectiveCamera(50, window.innerWidth / window.innerHeight, 0.05, 5000);
camera.position.set(0, 250, 350);

const controls = new OrbitControls(camera, ui.canvas);
controls.enableDamping = true;
controls.maxPolarAngle = Math.PI * 0.49;
controls.minDistance = 0.5;

scene.add(new THREE.HemisphereLight(0xdfeaf5, 0x4a4036, 1.4));
const sun = new THREE.DirectionalLight(0xfff3e0, 2.2);
scene.add(sun);
scene.add(sun.target);

const { material, uniforms } = createTerrainMaterial();
let terrain = new THREE.Group();
scene.add(terrain);
let pending: THREE.Group | null = null;

const hoverBox = new THREE.LineSegments(
  new THREE.EdgesGeometry(new THREE.BoxGeometry(1, 1, 1)),
  new THREE.LineBasicMaterial({ color: 0xffe066, depthTest: false, transparent: true }),
);
hoverBox.renderOrder = 10;
hoverBox.visible = false;
scene.add(hoverBox);

const sunDirection = new THREE.Vector3();
function updateSun(): void {
  const az = (Number(ui.sun.value) * Math.PI) / 180;
  const el = (35 * Math.PI) / 180;
  // Azimuth measured clockwise from north (−z).
  sunDirection.set(Math.sin(az) * Math.cos(el), Math.sin(el), -Math.cos(az) * Math.cos(el));
  ui.sunOut.textContent = `${ui.sun.value}°`;
}
updateSun();

// --- Worker / build orchestration -----------------------------------------

interface ActiveGrid {
  width: number;
  height: number;
  cellSize: number;
  heights: Float32Array;
  levels: Int32Array | null;
  baseLevel: number;
  exaggeration: number;
  mode: RenderMode;
}

const worker = new Worker(new URL('./terrain.worker.ts', import.meta.url), { type: 'module' });
let projection: Projection | null = null;
let elevationRange: [number, number] = [0, 0];
let tileCount = 0;
let jobId = 0;
let jobParams: { cellSize: number; exaggeration: number; mode: RenderMode } | null = null;
let pendingGrid: ActiveGrid | null = null;
let activeGrid: ActiveGrid | null = null;
let totalChunks = 0;

function setStatus(text: string, progress: number | null): void {
  ui.statusText.textContent = text;
  ui.status.classList.toggle('idle', progress === null);
  ui.statusBar.style.width = `${Math.round((progress ?? 0) * 100)}%`;
}

function currentParams() {
  return {
    cellSize: Number(ui.cell.value),
    exaggeration: Number(ui.exag.value),
    mode: (document.querySelector<HTMLInputElement>('input[name="mode"]:checked')?.value ?? 'voxel') as RenderMode,
  };
}

function requestBuild(): void {
  if (!projection) return;
  jobParams = currentParams();
  jobId++;
  if (pending) disposeGroup(pending);
  pending = new THREE.Group();
  pendingGrid = null;
  setStatus('Meshing…', 0);
  worker.postMessage({ type: 'build', jobId, ...jobParams });
}

let buildTimer = 0;
function scheduleBuild(): void {
  clearTimeout(buildTimer);
  buildTimer = window.setTimeout(requestBuild, 200);
}

function disposeGroup(group: THREE.Group): void {
  group.traverse((o) => {
    if (o instanceof THREE.Mesh) o.geometry.dispose();
  });
}

function fmt(n: number): string {
  return n.toLocaleString('en-US');
}

function renderStats(extra: Record<string, string>): void {
  const rows: Record<string, string> = {
    Tiles: String(tileCount),
    Elevation: `${elevationRange[0]}–${elevationRange[1]} m`,
    ...extra,
  };
  ui.stats.innerHTML = Object.entries(rows).map(([k, v]) => `<dt>${k}</dt><dd>${v}</dd>`).join('');
}

worker.onmessage = (e: MessageEvent<WorkerResponse>) => {
  const msg = e.data;
  switch (msg.type) {
    case 'loadProgress':
      setStatus(`Loading tiles ${msg.loaded}/${msg.total}`, msg.loaded / msg.total);
      break;
    case 'loaded': {
      projection = msg.projection;
      elevationRange = [msg.minElevation, msg.maxElevation];
      tileCount = msg.tileCount;
      const span = Math.max(projection.xMax - projection.xMin, projection.zMax - projection.zMin) / 1000;
      camera.position.set(0, span * 0.5, span * 0.7);
      camera.far = span * 8;
      camera.updateProjectionMatrix();
      controls.target.set(0, 0, 0);
      controls.maxDistance = span * 2.5;
      scene.fog = new THREE.Fog(SKY, span * 0.8, span * 3);
      renderStats({});
      requestBuild();
      break;
    }
    case 'buildStart':
      if (msg.jobId === jobId) totalChunks = msg.totalChunks;
      break;
    case 'grid':
      if (msg.jobId === jobId && jobParams) {
        pendingGrid = { ...msg, exaggeration: jobParams.exaggeration, mode: jobParams.mode };
      }
      break;
    case 'chunk': {
      if (msg.jobId !== jobId || !pending) break;
      if (msg.indices.length > 0) {
        const geometry = new THREE.BufferGeometry();
        geometry.setAttribute('position', new THREE.BufferAttribute(msg.positions, 3));
        geometry.setAttribute('normal', new THREE.BufferAttribute(msg.normals, 3, true));
        geometry.setIndex(new THREE.BufferAttribute(msg.indices, 1));
        geometry.computeBoundingSphere();
        geometry.computeBoundingBox();
        pending.add(new THREE.Mesh(geometry, material));
      }
      setStatus(`Meshing chunk ${msg.done}/${totalChunks}`, msg.done / Math.max(1, totalChunks));
      break;
    }
    case 'done': {
      if (msg.jobId !== jobId || !pending || !pendingGrid || !projection) break;
      scene.remove(terrain);
      disposeGroup(terrain);
      terrain = pending;
      pending = null;
      scene.add(terrain);
      activeGrid = pendingGrid;
      hoverDirty = true;
      uniforms.uExag.value = activeGrid.exaggeration;
      uniforms.uCell.value = activeGrid.cellSize / 1000;
      uniforms.uOrigin.value.set(projection.xMin / 1000, 0, projection.zMin / 1000);
      uniforms.uVoxel.value = activeGrid.mode === 'voxel' ? 1 : 0;
      setHeightTexture(activeGrid);
      updateGridUniform();
      setStatus(`Ready · built in ${(msg.ms / 1000).toFixed(2)} s`, null);
      renderStats({
        Grid: `${fmt(activeGrid.width)} × ${fmt(activeGrid.height)}`,
        Chunks: fmt(msg.chunks),
        Triangles: fmt(msg.triangles),
      });
      break;
    }
    case 'error':
      setStatus(`Error: ${msg.message}`, null);
      console.error(msg.message);
      break;
  }
};

function setHeightTexture(g: ActiveGrid): void {
  uniforms.uHeights.value?.dispose();
  const tex = new THREE.DataTexture(g.heights, g.width, g.height, THREE.RedFormat, THREE.FloatType);
  tex.minFilter = tex.magFilter = THREE.NearestFilter;
  tex.needsUpdate = true;
  uniforms.uHeights.value = tex;
}

function updateGridUniform(): void {
  uniforms.uGrid.value = ui.grid.checked && activeGrid?.mode === 'voxel' ? 1 : 0;
}

const tiles: TileInfo[] = Object.entries(tileUrls)
  .map(([path, url]) => {
    const parsed = parseTileName(path.split('/').pop() ?? path);
    return parsed ? { ...parsed, url } : null;
  })
  .filter((t): t is TileInfo => t !== null);
worker.postMessage({ type: 'load', tiles });

// --- UI events ---------------------------------------------------------------

ui.exag.addEventListener('input', () => {
  ui.exagOut.textContent = `${ui.exag.value}×`;
  scheduleBuild();
});
ui.cell.addEventListener('change', scheduleBuild);
document.querySelectorAll('input[name="mode"]').forEach((el) => el.addEventListener('change', scheduleBuild));
ui.sun.addEventListener('input', updateSun);
ui.grid.addEventListener('change', updateGridUniform);

window.addEventListener('resize', () => {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth, window.innerHeight);
});

// --- Hover / pick by marching the ray over the height field -------------------

interface Hit {
  point: THREE.Vector3;
  i: number;
  j: number;
  top: number;
}

function surfaceAt(g: ActiveGrid, x: number, z: number): { y: number; i: number; j: number } | null {
  const p = projection!;
  const km = g.cellSize / 1000;
  const fx = (x - p.xMin / 1000) / km;
  const fz = (z - p.zMin / 1000) / km;
  const i = Math.floor(fx);
  const j = Math.floor(fz);
  if (i < 0 || j < 0 || i >= g.width || j >= g.height) return null;
  if (g.levels) {
    const lv = g.levels[j * g.width + i];
    return lv === MISSING_LEVEL ? null : { y: lv * km, i, j };
  }
  if (Number.isNaN(g.heights[j * g.width + i])) return null;
  // Smooth vertices sit on cell corners (mean of the adjacent valid cells), matching the worker's mesh.
  const corner = (ci: number, cj: number) => {
    let sum = 0, n = 0;
    for (let jj = cj - 1; jj <= cj; jj++) {
      for (let ii = ci - 1; ii <= ci; ii++) {
        if (ii < 0 || jj < 0 || ii >= g.width || jj >= g.height) continue;
        const v = g.heights[jj * g.width + ii];
        if (!Number.isNaN(v)) { sum += v; n++; }
      }
    }
    return sum / n;
  };
  const tx = fx - i, tz = fz - j;
  const v =
    corner(i, j) * (1 - tx) * (1 - tz) + corner(i + 1, j) * tx * (1 - tz) +
    corner(i, j + 1) * (1 - tx) * tz + corner(i + 1, j + 1) * tx * tz;
  return Number.isNaN(v) ? null : { y: (v * g.exaggeration) / 1000, i, j };
}

const raycaster = new THREE.Raycaster();
function pick(clientX: number, clientY: number): Hit | null {
  const g = activeGrid;
  if (!g || !projection) return null;
  const ndc = new THREE.Vector2((clientX / window.innerWidth) * 2 - 1, -(clientY / window.innerHeight) * 2 + 1);
  raycaster.setFromCamera(ndc, camera);
  const ray = raycaster.ray;
  const km = g.cellSize / 1000;
  const maxY = (Math.max(elevationRange[1], 0) * g.exaggeration) / 1000 + km;
  const minY = g.levels ? g.baseLevel * km : (Math.min(elevationRange[0], 0) * g.exaggeration) / 1000 - km;
  const box = new THREE.Box3(
    new THREE.Vector3(projection.xMin / 1000, minY, projection.zMin / 1000),
    new THREE.Vector3(projection.xMax / 1000, maxY, projection.zMax / 1000),
  );
  // intersectBox returns the exit point when the camera is inside the box, so start at the camera instead.
  const entry = box.containsPoint(ray.origin) ? ray.origin.clone() : ray.intersectBox(box, new THREE.Vector3());
  if (!entry) return null;
  const step = km * 0.5;
  const pt = entry.clone();
  const dir = ray.direction;
  let prev: THREE.Vector3 | null = null;
  for (let n = 0; n < 50000 && box.containsPoint(pt); n++) {
    const s = surfaceAt(g, pt.x, pt.z);
    if (s && pt.y <= s.y) {
      // Refine between the last point above the surface and this one.
      let lo = prev ?? pt.clone(), hi = pt.clone();
      for (let k = 0; k < 8; k++) {
        const mid = lo.clone().lerp(hi, 0.5);
        const ms = surfaceAt(g, mid.x, mid.z);
        if (ms && mid.y <= ms.y) hi = mid; else lo = mid;
      }
      const hs = surfaceAt(g, hi.x, hi.z) ?? s;
      return { point: hi, i: hs.i, j: hs.j, top: hs.y };
    }
    prev = pt.clone();
    pt.addScaledVector(dir, step);
  }
  return null;
}

let lastPointer: { x: number; y: number } | null = null;
let hoverDirty = false;
ui.canvas.addEventListener('pointermove', (e) => {
  lastPointer = { x: e.clientX, y: e.clientY };
  hoverDirty = true;
});
ui.canvas.addEventListener('pointerleave', () => {
  lastPointer = null;
  hoverDirty = true;
});
controls.addEventListener('change', () => (hoverDirty = true));
ui.canvas.addEventListener('dblclick', (e) => {
  const hit = pick(e.clientX, e.clientY);
  if (hit) focusTarget = hit.point.clone();
});
let focusTarget: THREE.Vector3 | null = null;

function updateHover(): void {
  const g = activeGrid;
  const hit = lastPointer && g ? pick(lastPointer.x, lastPointer.y) : null;
  if (!hit || !g || !projection) {
    hoverBox.visible = false;
    ui.hover.textContent = '';
    return;
  }
  const km = g.cellSize / 1000;
  const x = projection.xMin / 1000 + (hit.i + 0.5) * km;
  const z = projection.zMin / 1000 + (hit.j + 0.5) * km;
  hoverBox.visible = true;
  hoverBox.scale.set(km, km, km);
  hoverBox.position.set(x, hit.top - km / 2, z);
  const { lat, lon } = unproject(projection, hit.point.x * 1000, hit.point.z * 1000);
  const elevation = g.heights[hit.j * g.width + hit.i];
  ui.hover.textContent =
    `${Math.abs(lat).toFixed(4)}° ${lat >= 0 ? 'N' : 'S'}, ${Math.abs(lon).toFixed(4)}° ${lon >= 0 ? 'E' : 'W'}` +
    ` · ${Math.round(elevation)} m (mean of ${g.cellSize >= 1000 ? `${g.cellSize / 1000} km` : `${g.cellSize} m`} cell)`;
}

// --- Loop -------------------------------------------------------------------

renderer.setAnimationLoop(() => {
  if (focusTarget) {
    const delta = focusTarget.clone().sub(controls.target).multiplyScalar(0.15);
    controls.target.add(delta);
    camera.position.add(delta);
    if (delta.lengthSq() < 1e-6) focusTarget = null;
  }
  controls.update();
  sun.target.position.copy(controls.target);
  sun.position.copy(controls.target).addScaledVector(sunDirection, 1000);
  if (hoverDirty) {
    hoverDirty = false;
    updateHover();
  }
  renderer.render(scene, camera);
});

if (import.meta.env.DEV) {
  (window as unknown as Record<string, unknown>).__vxle = { THREE, camera, controls, pick, hoverBox, get grid() { return activeGrid; } };
}
