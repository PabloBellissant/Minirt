# Asset Catalog

## Overview

miniRT loads assets from two locations:

1. **`asset/` directory** - Bundled with the repository. Contains `.rt` scene files, MTL materials, PPM textures, and small-to-medium OBJ meshes.
2. **`minirt-assets` submodule** - External repository at [https://github.com/ketodin/minirt-assets](https://github.com/ketodin/minirt-assets). Contains large OBJ meshes (high-poly models like BMW, Porsche, dragon) and high-resolution textures.

## Texture Naming Convention

Textures are stored in `asset/texture/<name>/` and follow a naming convention:

| File | Map Type |
|------|----------|
| `texture.ppm` | Diffuse/albedo (RGB) |
| `normal.ppm` | Normal map (RGB) |
| `roughness.ppm` | Roughness (grayscale) |
| `ambient.ppm` | Ambient occlusion (grayscale) |
| `metalness.ppm` | Metalness (grayscale) |

Available texture collections: sand, wood, tiles (3 variants), paving (2 variants), metal (2 variants), onyx, ornament. Each collection has a subset of the 5 map types above.

## Skyboxes

Seven equirectangular skyboxes are available in `asset/texture/skybox/`: nebula, space, snow, sky, indor, indorr (all PPM), and `mirrored_hall_4k.pfm` (HDR format).

## Materials

18 MTL material files under `asset/materials/`, covering textured surfaces (sand, wood, marble, onyx, tiles, checkerboard, paving, gold, leather, fence, foil, ornament, metal) and uniform materials under `asset/materials/uni/` (color, reflect, mat, emissive, transparent).

## OBJ Meshes

Small meshes bundled in the repo (triangle, square, glass-cube, monkey, cylinder, icosphere, funky, prism, difract). Large meshes in `minirt-assets` (bunny high/mid poly, BMW, casino, Porsche, Jesko, AMG, vinyl, Cornell box demo, chess set, chess room, dragon, Cornell box interior).

## Summary

| Asset Type | Repository | Count |
|------------|------------|-------|
| `.rt` scene files | main | 7 |
| MTL material files | main | 18 |
| Texture collections | main | 11 |
| Skyboxes | main | 7 |
| OBJ meshes (small) | main | 9 |
| OBJ meshes (large) | minirt-assets | 13 |
| UI assets (font + logos) | main | 5 |
