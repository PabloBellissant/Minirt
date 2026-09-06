# Wireframe Mode (Index 0)

Wireframe mode performs **CPU-side rasterization** of the scene geometry. It does not use OpenCL kernels - instead, it projects 3D points onto the 2D screen using the camera frustum and draws outlines directly into the pixel buffer.

## Source

`src/calc/render/rasterization/wireframe_render.c`

## Pipeline

```
wireframe_render()
  +-- fill_camera()          - compute camera basis vectors
  +-- clear_old_screen()     - ft_fbzero the pixel buffer
  +-- rasterize_objects()    - draw object outlines (white)
  |   +-- for each object: rasterize_outline_object()
  |       +-- sphere    -> rasterize_sphere_outline()
  |       +-- triangle  -> rasterize_triangle_outline()
  |       +-- plane     -> rasterize_plane_outline()
  |       +-- mesh      -> rasterize triangle fan
  +-- rasterize_lights()     - draw light circles
  |   +-- for each light: rasterize_light_outline()
  +-- returns 0
```

## Rasterization Details

### Object Outlines

All geometry types are rasterized as **wireframe outlines**. **Spheres** are projected as screen-space circles via `rasterize_sphere_outline()`. **Triangles** have three edge lines drawn with `rasterize_3d_line()`. **Planes** are projected as a bounded quad outline. **Meshes** rasterize each constituent triangle individually. All outlines are drawn in **white** (`rgb_int(255, 255, 255)`) by default.

![Wireframe render screenshot](docs/assets/img/bvh-volume-theme1.png)
*Screenshot of wireframe mode showing object outlines and light circles.*

### Light Circles

Lights are drawn as **yellow outlined circles** on screen via `rasterize_light_outline()`.

### Selection Highlight

After wireframe rasterization, the main loop calls `rasterize_selected()` to highlight the currently selected object in a distinct color.

### BVH Debug Overlay

When `data->params.bvh_debug` is `true` (toggled via the UI), `debug_rasterize_bvh()` draws the BVH hierarchy as an overlay on top of the wireframe. Each BVH node is rasterized in a **rainbow color** based on its depth, computed via `depth_to_rgb_int()` which maps depth to a rainbow gradient. The BVH shape type determines how each node is drawn: `BVH_AABB` nodes render as cuboid outlines (8 vertices, 12 edges), `BVH_SPHERE` nodes render as sphere outline circles, and `BVH_OBB` nodes render as transformed cuboids using quaternion rotation. The `bvh_depth` parameter controls which depths are visible (`-1` = all depths).

### Projection

All 3D-to-2D projection uses `project_point()`, which applies the camera model via `t_vec2i project_point(const t_vec3 *p, const t_camera *camera, const t_img_data *img)`.