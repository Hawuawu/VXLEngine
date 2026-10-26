export type RenderMode = 'voxel' | 'smooth';

export interface TileInfo {
  name: string;
  /** Latitude of the tile's south edge, degrees (negative = south). */
  lat: number;
  /** Longitude of the tile's west edge, degrees (negative = west). */
  lon: number;
  url: string;
}

/** Local equirectangular projection; x grows east, z grows south, units are metres. */
export interface Projection {
  lat0: number;
  lon0: number;
  kx: number;
  kz: number;
  xMin: number;
  xMax: number;
  zMin: number;
  zMax: number;
}

export interface BuildRequest {
  type: 'build';
  jobId: number;
  cellSize: number;
  exaggeration: number;
  mode: RenderMode;
}

export type WorkerRequest = { type: 'load'; tiles: TileInfo[] } | BuildRequest;

export type WorkerResponse =
  | { type: 'loadProgress'; loaded: number; total: number }
  | { type: 'loaded'; projection: Projection; minElevation: number; maxElevation: number; tileCount: number }
  | { type: 'buildStart'; jobId: number; totalChunks: number }
  | {
      type: 'grid';
      jobId: number;
      width: number;
      height: number;
      cellSize: number;
      heights: Float32Array;
      levels: Int32Array | null;
      baseLevel: number;
    }
  | { type: 'chunk'; jobId: number; done: number; positions: Float32Array; normals: Int8Array; indices: Uint32Array }
  | { type: 'done'; jobId: number; chunks: number; triangles: number; ms: number }
  | { type: 'error'; message: string };

export const MISSING_LEVEL = -2147483648;

const TILE_NAME = /([NS])(\d{1,2})([EW])(\d{1,3})/i;

export function parseTileName(fileName: string): { name: string; lat: number; lon: number } | null {
  const m = TILE_NAME.exec(fileName);
  if (!m) return null;
  const lat = Number(m[2]) * (m[1].toUpperCase() === 'S' ? -1 : 1);
  const lon = Number(m[4]) * (m[3].toUpperCase() === 'W' ? -1 : 1);
  return { name: m[0].toUpperCase(), lat, lon };
}

export function unproject(p: Projection, xMetres: number, zMetres: number): { lat: number; lon: number } {
  return { lat: p.lat0 - zMetres / p.kz, lon: p.lon0 + xMetres / p.kx };
}
