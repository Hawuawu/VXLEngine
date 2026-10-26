import { defineConfig } from 'vite';

export default defineConfig({
  base: './',
  server: { fs: { allow: ['..'] } },
  worker: { format: 'es' },
  build: { chunkSizeWarningLimit: 1024 },
});
