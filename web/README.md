# VXLEngine web renderer

Browser-based voxel / heightmap terrain renderer for the SRTM tiles in [`../SRTM`](../SRTM).
Built with Vite, TypeScript and three.js.

```sh
cd web
npm install
npm run dev       # http://localhost:5173
npm run build     # static site in web/dist (tiles are copied as assets)
```

## How it works

- `src/main.ts` finds every `../SRTM/*.hgt.zip` at build time (`import.meta.glob`) and passes the URLs to a worker.
- `src/terrain.worker.ts`:
  - downloads and unzips the tiles (`fflate`) and decodes the big-endian int16 `.hgt` grids. Tile size is detected, so SRTM1 (3601²) works too; void samples (-32768) are skipped.
  - projects all tiles onto one local equirectangular metric grid and box-filters the raw samples into square cells of the chosen resolution.
  - **Voxel mode** quantises the exaggerated height into cube-sized levels, then greedy-merges top faces of equal level and merges side walls into runs. Each chunk is 128×128 cells.
  - **Smooth mode** builds a regular grid mesh per chunk with central-difference normals.
  - sends the chunk buffers back as transferables. A newer build request cancels an older one.
- The terrain shader colours by real elevation (hypsometric tint) and draws block outlines from world position, so merged faces still look like individual voxels.
- Hover/pick marches the camera ray over the same height grid to show lat/lon/elevation without CPU raycasting against the meshes.

Controls: drag to rotate, right-drag to pan, scroll to zoom, double-click to focus on a point.
