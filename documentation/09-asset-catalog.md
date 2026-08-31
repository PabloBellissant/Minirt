# Asset Catalog

## Overview

miniRT ships with a rich set of assets: scene files (`.rt`), OBJ meshes,
textures, skyboxes, and a font file. All assets are stored under the
`asset/` directory.

A dedicated repository with additional test maps and assets is available at
**[https://github.com/ketodin/minirt-assets](https://github.com/ketodin/minirt-assets)**.

---

## Scene Files (`.rt`)

| File | Description |
|------|-------------|
| `asset/42.rt` | 42 School subject scene — 500+ spheres arranged in a grid, with camera, ambient light, and a single point light. Used as the default test scene. |
| `asset/scenes/template.rt` | Default scene template with OBJ mesh objects and multiple materials (gold, glass, marble). Demonstrates full material system. |
| `asset/scenes/cornell.rt` | Cornell box scene with the Stanford Bunny mesh inside. Tests indirect lighting and color bleeding. |
| `asset/scenes/rgb.rt` | RGB test scene with colored glass spheres and a skybox. Tests refraction and dispersion. |
| `asset/scenes/chess.rt` | Chess room scene with a chess set on a board. Tests complex geometry and multiple OBJ references. |
| `asset/scenes/marble.rt` | Material showcase with spheres of marble, onyx, and gold using PBR textures. |
| `asset/scenes/refract.rt` | Refraction test scene with glass shapes and transparent materials. |

---

## OBJ Meshes

### High-Polygonal Car Models

| Path | Description |
|------|-------------|
| `asset/AMG/amg.obj` | Mercedes-Benz SLR McLaren 722 Edition — detailed car model with interior |
| `asset/jesko/jesko.obj` | Koenigsegg Jesko — hypercar with complex body panels |
| `asset/porsche/porsche.obj` | Porsche 911 — classic sports car model |
| `asset/bmw/bmw.obj` | BMW M5 F90 — sedan with carbon fiber details |

### Stanford Models

| Path | Description |
|------|-------------|
| `asset/bunny/bunny_low_poly.obj` | Stanford Bunny — low polygon count (~1000 faces) |
| `asset/bunny/bunny_mid_poly.obj` | Stanford Bunny — medium polygon count |
| `asset/bunny/bunny_high_poly.obj` | Stanford Bunny — high polygon count (~70,000 faces) |
| `asset/bunny/stanford_bunny.obj` | Stanford Bunny — original scan |

### Scene Props

| Path | Description |
|------|-------------|
| `asset/cornellbox/cornellbox.obj` | Cornell box — classic radiosity test scene |
| `asset/cornel/cornell-box.obj` | Cornell box variant with glass cube |
| `asset/cornel/glass-cube.obj` | Glass cube for refraction tests |
| `asset/cornel/demo.obj` | Demo object for Cornell box |
| `asset/casino/casino.obj` | Casino interior — detailed room with tables and decor |
| `asset/casino/cas.obj` | Casino prop |
| `asset/chess/chess.obj` | Chess set — board, pieces (king, queen, bishop, knight, rook, pawn) |
| `asset/chess/room.obj` | Chess room — walls, floor, lighting elements |

### Abstract / Test Objects

| Path | Description |
|------|-------------|
| `asset/dragon/dragon.obj` | Dragon sculpture — complex organic model |
| `asset/difract/difract.obj` | Refraction test object — glass prism for dispersion tests |
| `asset/square.obj` | Simple square plane (2 triangles) |
| `asset/triangle/triangle.obj` | Single triangle |
| `asset/prism/prism.obj` | Triangular prism |
| `asset/living_room/living_room.obj` | Living room interior |

### Half Primitives (`asset/half/`)

| Path | Description |
|------|-------------|
| `asset/half/cylinder.obj` | Cylinder primitive |
| `asset/half/cyl.obj` | Alternative cylinder |
| `asset/half/icosphere.obj` | Icosphere (geodesic sphere) |
| `asset/half/monkey.obj` | Blender Suzanne monkey head |
| `asset/half/prism.obj` | Prism shape |
| `asset/half/circle.obj` | Circle/disk primitive |
| `asset/half/funky.obj` | Funky abstract shape |

---

## Texture Directories

All textures are in `asset/texture/`. Each subdirectory contains a `texture.ppm`
(diffuse/albedo) and may include additional maps.

### Material Texture Sets

| Directory | Maps | Description |
|-----------|------|-------------|
| `asset/texture/checkerboard/` | texture, metalness | Checkerboard pattern with metalness map |
| `asset/texture/fence/` | texture, roughness, normal, opacity | Wooden fence with transparency |
| `asset/texture/foil/` | _(included via scenes)_ | Metallic foil |
| `asset/texture/gold/` | texture, roughness, normal, metalness | Brushed gold surface |
| `asset/texture/leather/` | texture, roughness, normal | Leather surface |
| `asset/texture/marble/1/` | texture, roughness, normal | White marble |
| `asset/texture/marble/2/` | texture, roughness, normal | Dark marble |
| `asset/texture/metal/1/` | texture, roughness, normal | Raw metal |
| `asset/texture/metal/2/` | texture, roughness, normal, metalness | Polished metal |
| `asset/texture/onyx/` | texture, roughness, normal | Onyx stone |
| `asset/texture/ornament/` | texture, roughness, normal | Decorative ornament pattern |
| `asset/texture/paving/1/` | texture, roughness, normal, ambient | Stone paving (style 1) |
| `asset/texture/paving/2/` | texture, roughness, normal, ambient | Stone paving (style 2), has one `.png` (ambient) |
| `asset/texture/sand/` | texture, roughness, normal, ambient | Sand surface |
| `asset/texture/tiles/1/` | texture, roughness, normal, ambient | Ceramic tiles (style 1) |
| `asset/texture/tiles/2/` | texture, roughness, normal | Ceramic tiles (style 2) |
| `asset/texture/tiles/3/` | texture, roughness, normal, ambient | Ceramic tiles (style 3) |
| `asset/texture/wood/` | texture, roughness, normal, ambient | Wood planks |
| `asset/texture/bmw/` | Multiple `.ppm` files | BMW M5 specific textures (carbon fiber, radiator, interior, badges, plate number, grille alpha) |
| `asset/texture/chess/` | Multiple `.ppm` files | Chess piece and board textures |

---

## Skybox Textures

| Path | Description |
|------|-------------|
| `asset/texture/skybox/nebula.ppm` | Nebula/space skybox — colorful cosmic background |
| `asset/texture/skybox/space.ppm` | Outer space starfield |
| `asset/texture/skybox/sky.ppm` | Blue sky with clouds |
| `asset/texture/skybox/snow.ppm` | Snowy mountain landscape |
| `asset/texture/skybox/indor.ppm` | Indoor environment (version 1) |
| `asset/texture/skybox/indorr.ppm` | Indoor environment (version 2) |

Skyboxes are used when a ray misses all scene geometry. The skybox texture
is selected via the `sky` keyword in `.rt` scene files (`sky path.ppm`).

---

## Font File

| File | Description |
|------|-------------|
| `asset/fonts/JetBrainsMono-ExtraLight.ttf` | JetBrains Mono ExtraLight — monospace font used by `font_renderer` for FPS counter and UI text rendering (currently commented out in display code) |

---

## Complete Asset Table

| Category | Asset | Path | Format |
|----------|-------|------|--------|
| Scene | 42 Subject | `asset/42.rt` | `.rt` |
| Scene | Template | `asset/scenes/template.rt` | `.rt` |
| Scene | Cornell Box | `asset/scenes/cornell.rt` | `.rt` |
| Scene | RGB Test | `asset/scenes/rgb.rt` | `.rt` |
| Scene | Chess Room | `asset/scenes/chess.rt` | `.rt` |
| Scene | Marble | `asset/scenes/marble.rt` | `.rt` |
| Scene | Refraction Test | `asset/scenes/refract.rt` | `.rt` |
| Mesh | McLaren SLR 722 | `asset/AMG/amg.obj` | `.obj` |
| Mesh | Koenigsegg Jesko | `asset/jesko/jesko.obj` | `.obj` |
| Mesh | Porsche 911 | `asset/porsche/porsche.obj` | `.obj` |
| Mesh | BMW M5 | `asset/bmw/bmw.obj` | `.obj` |
| Mesh | Stanford Bunny (low) | `asset/bunny/bunny_low_poly.obj` | `.obj` |
| Mesh | Stanford Bunny (mid) | `asset/bunny/bunny_mid_poly.obj` | `.obj` |
| Mesh | Stanford Bunny (high) | `asset/bunny/bunny_high_poly.obj` | `.obj` |
| Mesh | Stanford Bunny (orig) | `asset/bunny/stanford_bunny.obj` | `.obj` |
| Mesh | Dragon | `asset/dragon/dragon.obj` | `.obj` |
| Mesh | Cornell Box | `asset/cornellbox/cornellbox.obj` | `.obj` |
| Mesh | Cornell Box (alt) | `asset/cornel/cornell-box.obj` | `.obj` |
| Mesh | Glass Cube | `asset/cornel/glass-cube.obj` | `.obj` |
| Mesh | Cornell Demo | `asset/cornel/demo.obj` | `.obj` |
| Mesh | Casino Interior | `asset/casino/casino.obj` | `.obj` |
| Mesh | Casino Prop | `asset/casino/cas.obj` | `.obj` |
| Mesh | Chess Set | `asset/chess/chess.obj` | `.obj` |
| Mesh | Chess Room | `asset/chess/room.obj` | `.obj` |
| Mesh | Prism | `asset/prism/prism.obj` | `.obj` |
| Mesh | Square | `asset/square.obj` | `.obj` |
| Mesh | Triangle | `asset/triangle/triangle.obj` | `.obj` |
| Mesh | Difract | `asset/difract/difract.obj` | `.obj` |
| Mesh | Living Room | `asset/living_room/living_room.obj` | `.obj` |
| Mesh | Cylinder | `asset/half/cylinder.obj` | `.obj` |
| Mesh | Cyl (alt) | `asset/half/cyl.obj` | `.obj` |
| Mesh | Icosphere | `asset/half/icosphere.obj` | `.obj` |
| Mesh | Suzanne | `asset/half/monkey.obj` | `.obj` |
| Mesh | Half Prism | `asset/half/prism.obj` | `.obj` |
| Mesh | Circle | `asset/half/circle.obj` | `.obj` |
| Mesh | Funky | `asset/half/funky.obj` | `.obj` |
| Texture | Checkerboard | `asset/texture/checkerboard/` | `.ppm` (2 files) |
| Texture | Fence | `asset/texture/fence/` | `.ppm` (4 files) |
| Texture | Gold | `asset/texture/gold/` | `.ppm` (4 files) |
| Texture | Leather | `asset/texture/leather/` | `.ppm` (3 files) |
| Texture | Marble 1 | `asset/texture/marble/1/` | `.ppm` (3 files) |
| Texture | Marble 2 | `asset/texture/marble/2/` | `.ppm` (3 files) |
| Texture | Metal 1 | `asset/texture/metal/1/` | `.ppm` (3 files) |
| Texture | Metal 2 | `asset/texture/metal/2/` | `.ppm` (4 files) |
| Texture | Onyx | `asset/texture/onyx/` | `.ppm` (3 files) |
| Texture | Ornament | `asset/texture/ornament/` | `.ppm` (3 files) |
| Texture | Paving 1 | `asset/texture/paving/1/` | `.ppm` (4 files) |
| Texture | Paving 2 | `asset/texture/paving/2/` | `.ppm` (3) + `.png` (1) |
| Texture | Sand | `asset/texture/sand/` | `.ppm` (4 files) |
| Texture | Tiles 1 | `asset/texture/tiles/1/` | `.ppm` (4 files) |
| Texture | Tiles 2 | `asset/texture/tiles/2/` | `.ppm` (3 files) |
| Texture | Tiles 3 | `asset/texture/tiles/3/` | `.ppm` (4 files) |
| Texture | Wood | `asset/texture/wood/` | `.ppm` (4 files) |
| Texture | BMW M5 | `asset/texture/bmw/` | `.ppm` (8 files) |
| Texture | Chess | `asset/texture/chess/` | `.ppm` (5 files) |
| Skybox | Nebula | `asset/texture/skybox/nebula.ppm` | `.ppm` |
| Skybox | Space | `asset/texture/skybox/space.ppm` | `.ppm` |
| Skybox | Sky | `asset/texture/skybox/sky.ppm` | `.ppm` |
| Skybox | Snow | `asset/texture/skybox/snow.ppm` | `.ppm` |
| Skybox | Indor | `asset/texture/skybox/indor.ppm` | `.ppm` |
| Skybox | Indorr | `asset/texture/skybox/indorr.ppm` | `.ppm` |
| Font | JetBrains Mono | `asset/fonts/JetBrainsMono-ExtraLight.ttf` | `.ttf` |

---

## External Assets Repository

A dedicated repository containing additional maps, scenes, and test assets
for miniRT is available at:

**https://github.com/ketodin/minirt-assets**

Clone it alongside the project for extra scenes and models to render.