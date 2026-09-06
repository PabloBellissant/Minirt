# Asset Catalog

## Overview

*Visual catalog grid showing available scene files, OBJ meshes, MTL materials, and texture maps organized by type, giving an at-a-glance view of all available assets.*

miniRT loads scene files, OBJ meshes, MTL materials, and texture maps from
two locations:

1. **`asset/` directory** - Bundled with the repository. Contains scene
   files (`.rt`), MTL material definitions, and small-to-medium texture
   maps and OBJ meshes.
2. **`minirt-assets` submodule** - External repository at
   [https://github.com/ketodin/minirt-assets](https://github.com/ketodin/minirt-assets).
   Contains large OBJ meshes (high-poly models) and high-resolution texture
   maps that are too large for the main repository.

### Submodule Setup

The `minirt-assets` submodule is declared in `.gitmodules`:

```
[submodule "minirt-assets"]
    path = minirt-assets
    url = git@github.com:ketodin/minirt-assets.git
```

To fetch all assets:

```bash
git submodule init && git submodule sync && git submodule update --remote
```

The `minirt-assets` repository mirrors the internal directory structure of
`asset/`: mesh files in `asset/`, textures in `asset/texture/`, materials in
`asset/materials/`, and OBJ files in `asset/<model_name>/`.

---

## assets/ Directory (UI Assets)

These small assets are kept in the main repository under `assets/`.

| Path | Type | Description |
|------|------|-------------|
| `assets/fonts/JetBrainsMono-ExtraLight.ttf` | TTF font | UI typeface |
| `assets/ui_logo/wireframe-logo.pam` | PAM image | Render mode switch: Wireframe |
| `assets/ui_logo/phong-logo.pam` | PAM image | Render mode switch: Phong |
| `assets/ui_logo/pbr-logo.pam` | PAM image | Render mode switch: PBR |
| `assets/ui_logo/monte-carlo-logo.pam` | PAM image | Render mode switch: Monte Carlo |
| `assets/material_preview.rt` | `.rt` scene | Material preview test scene |

---

## asset/scenes/ Directory - Scene Files

| File | Description | Key Features |
|------|-------------|-------------|
| `asset/scenes/template.rt` | Template/test scene | OBJ meshes (glass cube, monkey, difract, square), checkerboard plane, MTL materials (sand, checkerboard, uni/mat, emissive, transparent) |
| `asset/scenes/cornell.rt` | Cornell box | Cornell box OBJ, mid-poly bunny, transparent/reflect/emissive materials |
| `asset/scenes/chess.rt` | Chess scene | Room OBJ, chess set OBJ, wood material, emissive ceiling light |
| `asset/scenes/marble.rt` | Marble gallery | Marble/onyx/tiles/gold spheres on tiled planes |
| `asset/scenes/rgb.rt` | RGB test | Glass spheres with emissive RGB centers, sand plane |
| `asset/scenes/refract.rt` | Refraction test | Emissive light, prism OBJ, checkerboard plane, glass material |
| `asset/42.rt` | 42 logo scene | Large number of small colored spheres forming 42 pattern |

### Scene File Format

Each `.rt` file uses a line-based text format:

```
C x,y,z dx,dy,dz FOV        # Camera
A intensity R,G,B           # Ambient light
L x,y,z brightness R,G,B    # Point light
sp x,y,z diameter R,G,B [material]  # Sphere
pl x,y,z nx,ny,nz R,G,B [material] [scaling]  # Plane
cy x,y,z nx,ny,nz diameter height R,G,B [material]  # Cylinder
mtl path_to_mtl.mtl         # Load MTL library
obj path_to.obj x,y,z rx,ry,rz sx,sy,sz  # Load OBJ mesh
sky path_to_texture.ppm     # Skybox
```

---

## asset/ Directory - Texture Maps

Textures are stored in `asset/texture/<name>/` and follow a naming convention:

| File | Map Type |
|------|----------|
| `texture.ppm` | Diffuse/albedo (RGB) |
| `normal.ppm` | Normal map (RGB) |
| `roughness.ppm` | Roughness (grayscale) |
| `ambient.ppm` | Ambient occlusion (grayscale) |
| `metalness.ppm` | Metalness (grayscale) |

### Texture Collections

| Collection | Path | Maps Available |
|------------|------|----------------|
| Sand | `asset/texture/sand/` | texture, normal, roughness, ambient |
| Wood | `asset/texture/wood/` | texture, normal, roughness, ambient |
| Tiles 1 | `asset/texture/tiles/1/` | texture, normal, roughness, ambient |
| Tiles 2 | `asset/texture/tiles/2/` | texture, normal, roughness |
| Tiles 3 | `asset/texture/tiles/3/` | texture, normal, roughness, ambient |
| Paving 1 | `asset/texture/paving/1/` | texture, normal, roughness, ambient |
| Paving 2 | `asset/texture/paving/2/` | texture, normal, roughness, ambient, ambient.png |
| Metal 1 | `asset/texture/metal/1/` | texture, normal, roughness |
| Metal 2 | `asset/texture/metal/2/` | texture, normal, roughness, metalness |
| Onyx | `asset/texture/onyx/` | texture, normal, roughness |
| Ornament | `asset/texture/ornament/` | texture, normal, roughness |

### Skyboxes

| Path | Type | Description |
|------|------|-------------|
| `asset/texture/skybox/nebula.ppm` | Equirectangular | Nebula space skybox |
| `asset/texture/skybox/space.ppm` | Equirectangular | Starfield |
| `asset/texture/skybox/snow.ppm` | Equirectangular | Snowy landscape |
| `asset/texture/skybox/sky.ppm` | Equirectangular | Blue sky with clouds |
| `asset/texture/skybox/indor.ppm` | Equirectangular | Indoor room |
| `asset/texture/skybox/indorr.ppm` | Equirectangular | Indoor room (variant) |
| `asset/texture/skybox/mirrored_hall_4k.pfm` | HDR equirectangular | Mirrored hall (PFM format) |

---

## asset/ Directory - MTL Materials

Materials are defined in `.mtl` files under `asset/materials/`. They follow
the Wavefront OBJ MTL format with extensions.

| MTL File | Description |
|----------|-------------|
| `asset/materials/sand.mtl` | Sandy texture (diffuse + normal + roughness + AO) |
| `asset/materials/wood.mtl` | Wood texture |
| `asset/materials/marble.mtl` | Marble texture |
| `asset/materials/onyx.mtl` | Onyx stone texture |
| `asset/materials/tiles.mtl` | Tiles texture |
| `asset/materials/checkerboard.mtl` | Procedural checkerboard |
| `asset/materials/paving.mtl` | Paving stone texture |
| `asset/materials/gold.mtl` | Gold (metallic KS) |
| `asset/materials/leather.mtl` | Leather texture |
| `asset/materials/fence.mtl` | Fence texture |
| `asset/materials/foil.mtl` | Foil texture |
| `asset/materials/ornament.mtl` | Ornament texture |
| `asset/materials/metal.mtl` | Metal material |
| `asset/materials/uni/color.mtl` | Uniform color (no texture) |
| `asset/materials/uni/reflect.mtl` | Uniform reflective |
| `asset/materials/uni/mat.mtl` | Uniform basic material |
| `asset/materials/uni/emissive.mtl` | Uniform emissive (white/red/green/blue variants) |
| `asset/materials/uni/transparent.mtl` | Uniform glass (transparent with IOR) |

---

## asset/ Directory - OBJ Meshes

Small OBJ meshes bundled in the repository. Large meshes are in
`minirt-assets`.

| Path | Description |
|------|-------------|
| `asset/triangle/triangle.obj` | Single triangle (test) |
| `asset/square.obj` | Square plane |
| `asset/cornel/glass-cube.obj` | Glass cube for Cornell box |
| `asset/half/monkey.obj` | Suzanne (mid-poly) |
| `asset/half/cylinder.obj` | Cylinder (polygonal) |
| `asset/half/icosphere.obj` | Icosphere |
| `asset/half/funky.obj` | Funky shape |
| `asset/prism/prism.obj` | Prism |
| `asset/difract/difract.obj` | Diffraction shape |

### Large Assets (in `minirt-assets`)

The following assets require the `minirt-assets` submodule:

| Model | Description |
|-------|-------------|
| `asset/bunny/bunny_high_poly.obj` | Stanford bunny (high resolution) |
| `asset/bunny/bunny_mid_poly.obj` | Stanford bunny (mid resolution) |
| `asset/bmw/bmw.obj` | BMW car model |
| `asset/casino/casino.obj` | Casino building |
| `asset/porsche/porsche.obj` | Porsche car model |
| `asset/jesko/jesko.obj` | Koenigsegg Jesko |
| `asset/AMG/amg.obj` | Mercedes AMG |
| `asset/vinyl/vinyl.obj` | Vinyl record |
| `asset/cornel/demo.obj` | Full Cornell box demo |
| `asset/chess/chess.obj` | Chess set |
| `asset/chess/room.obj` | Chess room |
| `asset/dragon/dragon.obj` | Dragon model |
| `asset/cornel/cornell-box.obj` | Cornell box interior |

---

## Summary Table

| Asset Type | Repository | Count (approx.) |
|------------|------------|-----------------|
| `.rt` scene files | main | 7 |
| MTL material files | main | 20+ |
| Texture maps (PPM) | main | 40+ |
| OBJ meshes (small) | main | 10+ |
| UI logos (PAM) | main | 4 |
| Fonts | main | 1 |
| OBJ meshes (large) | minirt-assets | 15+ |
| Texture maps (large/HDR) | minirt-assets | 10+ |