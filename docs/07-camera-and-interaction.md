# Camera and Interaction

## Overview

miniRT provides a full 6-degree-of-freedom camera with Euler-angle rotation, a configurable viewport, thin-lens depth of field, and real-time exposure control. The camera state is held in `t_camera` (`include/render.h`, lines 26-39):

```c
typedef struct s_camera
{
    cl_float3   pos;            // World-space position
    cl_float3   rot;            // Euler angles: yaw (y), pitch (x), roll (z)
    cl_float3   camera_forward; // Orthonormal basis: forward vector
    cl_float3   camera_right;   // Orthonormal basis: right vector
    cl_float3   camera_up;      // Orthonormal basis: up vector
    cl_float3   pixel_delta_u;  // Viewport: horizontal pixel step
    cl_float3   pixel_delta_v;  // Viewport: vertical pixel step
    cl_float3   pixel00_loc;    // Viewport: top-left pixel world position
    cl_int      fov;            // Field of view in degrees
    cl_int      frame;          // Accumulation frame counter
    cl_float    lens_radius;    // DOF: aperture radius (0 = pinhole)
    cl_float    focus_dist;     // DOF: focal plane distance
}               t_camera;
```

*Diagram showing the camera position, viewport, forward/right/up basis vectors, and depth of field parameters.*

---

## Camera Model: Euler Angles

The camera uses **yaw-pitch-roll** Euler angles stored in `rot`, where `rot.y` controls **Yaw** (left/right rotation around Y axis), `rot.x` controls **Pitch** (up/down rotation around X axis), and `rot.z` controls **Roll** (tilt around forward axis).

### Forward/Rotation Calculation

`apply_yaw_and_pitch()` in `camera_utils.c` computes the orthonormal basis from Euler angles. The forward vector is computed as:

```c
cam->camera_forward = (t_vec3){{
    sinf(cam->rot.y) * cosf(cam->rot.x),
    sinf(cam->rot.x),
    cosf(cam->rot.y) * cosf(cam->rot.x)
}};
```

The **right** and **up** vectors are derived from yaw-only for the horizontal basis, then roll-rotated around the forward axis.

### Viewport

`fill_camera()` recomputes the viewport whenever the camera or image dimensions change:

```
viewport_height = 2.0 x tan(FOV x pi / 180 / 2.0)
viewport_width = viewport_height x (width / height)
```

The viewport is centered on the forward axis at unit distance from the camera position. `pixel00_loc` is the world-space coordinate of the top-left pixel (accounting for half-pixel offset).

---

## Depth of Field (Thin Lens Approximation)

The GPU ray generation in `calc_rays.cl` implements a thin-lens DOF model. Sub-pixel jitter provides antialiasing. The ray direction is initially computed toward the pixel center, then the focal point is determined by extending the ray to `focus_dist`. A random point on a disk (scaled by `lens_radius`) is sampled, and the final ray origin is offset by this lens sample while the direction is re-targeted toward the focal point.

**`focus_dist`** controls the distance at which objects are perfectly in focus (zero circle of confusion), adjustable via `T` (increase x1.05) and `G` (decrease /1.05) with range [0.2, 10000]. **`lens_radius`** controls the aperture size; larger values produce a shallower depth of field (more blur), adjustable via `Y` (increase x1.05) and `H` (decrease /1.05) with range [0.0, 0.5]. When `lens_radius = 0`, the camera acts as a perfect pinhole with no DOF.

![Depth of field comparison](docs/assets/img/depth-of-field.png)
*Comparison of pinhole (lens_radius=0) vs. shallow DOF (lens_radius > 0) with focus on a specific object.*

---

## Exposure Control

**New in this version:** Real-time exposure control via `F5` / `F6`. Pressing F5 multiplies exposure by 1.3 (brighten) and F6 divides by 1.3 (darken). Exposure is stored as `data->params.exposure` (a float) and applied in the `draw_accu` kernel as a multiplier on the sample count divisor. Higher exposure produces a smaller divisor and brighter image. This is purely a post-process multiplier on the accumulation buffer and requires no re-rendering. Default exposure is `1.0`.

---

## Movement Speed

Movement speed in `camera_move.c` uses a base speed of 5 units/second. Holding **Ctrl** doubles the speed via `const float step = MOVE_SPEED * (1 + RUN_SPEED * ctrl) * delta_time` where `RUN_SPEED=5`, making the multiplier `1 + 5 = 6` when Ctrl is held. Roll sensitivity is `0.03` radians per frame and mouse look sensitivity is `0.003` radians per pixel movement.

---

## Complete Key Binding Table

### Camera Movement

| Key | Action |
|---|---|
| `W` | Move forward (in horizontal look direction) |
| `S` | Move backward |
| `A` | Move left (strafe) |
| `D` | Move right (strafe) |
| `Space` | Move up (world Y) |
| `Shift` | Move down (world Y) |
| `Ctrl` (held) | Double movement speed |
| `Q` | Roll left (counter-clockwise) |
| `E` | Roll right (clockwise) |
| Mouse (when focused) | Yaw / pitch look |

### Depth of Field

| Key | Action |
|---|---|
| `T` | Increase focus distance (x1.05) |
| `G` | Decrease focus distance (/1.05) |
| `Y` | Increase lens radius / aperture (x1.05) |
| `H` | Decrease lens radius / aperture (/1.05) |

### Render Mode

| Key | Mode |
|---|---|
| `1` | Wireframe (CPU rasterized debug view) |
| `2` | Phong (GPU: ambient + diffuse + specular + emissive) |
| `3` | PBR (GPU: Fresnel, reflection, refraction, bounces) |
| `4` | Monte Carlo (GPU: path tracing, GGX, dispersion) |
| `-` | Normal Debug (GPU: surface normals -> RGB) |
| `=` | Heat Map (GPU: BVH traversal depth heat map) |

### BVH Debug

| Key | Action |
|---|---|
| `V` | Toggle BVH debug overlay (bounding box wireframe visualization) |
| `Up` | Increase displayed BVH depth (fewer, shallower boxes) |
| `Down` | Decrease displayed BVH depth (more, deeper boxes) |
| `Left` | Switch to previous BVH mode (sphere -> AABB -> OBB cycle) |
| `Right` | Switch to next BVH mode (sphere -> AABB -> OBB cycle) |
| `C` | Cycle BVH heat map color palette offset (0-9) |

### UI / Display

| Key | Action |
|---|---|
| `M` | Cycle UI mode: full UI -> minimal (render switch only) -> hidden |
| `K` | Toggle mouse focus (confine pointer to window for look) |
| `F5` | Increase exposure (x1.3) |
| `F6` | Decrease exposure (/1.3) |
| `F11` | Export current scene to `.rt` file |
| `F12` | Schedule render task (hides UI, renders clean frame, exports PPM) |

### Summary Table (all 27+ keys)

| Key | Category | Action |
|---|---|---|
| `W` | Movement | Forward |
| `S` | Movement | Backward |
| `A` | Movement | Left strafe |
| `D` | Movement | Right strafe |
| `Space` | Movement | Up (world Y) |
| `Shift` | Movement | Down (world Y) |
| `Ctrl` | Movement | Speed boost (x6) |
| `Q` | Movement | Roll left |
| `E` | Movement | Roll right |
| `Mouse` | Look | Yaw/pitch |
| `T` | DOF | Up focus distance |
| `G` | DOF | Down focus distance |
| `Y` | DOF | Up lens radius |
| `H` | DOF | Down lens radius |
| `1` | Render | Wireframe |
| `2` | Render | Phong |
| `3` | Render | PBR |
| `4` | Render | Monte Carlo |
| `-` | Render | Normal Debug |
| `=` | Render | Heat Map |
| `V` | BVH Debug | Toggle overlay |
| `Up` | BVH Debug | Up Depth |
| `Down` | BVH Debug | Down Depth |
| `Left` | BVH Debug | Prev mode |
| `Right` | BVH Debug | Next mode |
| `C` | BVH Debug | Cycle palette |
| `M` | UI | Cycle UI mode |
| `K` | UI | Toggle mouse focus |
| `F5` | Exposure | Increase |
| `F6` | Exposure | Decrease |
| `F11` | Export | Scene to `.rt` |
| `F12` | Export | Render task (PPM screenshot) |

---

## Mouse Look

Mouse look is implemented in `mouse_hooks.c`. `cam_move()` is called on every mouse move event, computing `delta_pos = current_pos - last_pos`. If `mouse_input.focus` is `true`, `handle_camera_rotation()` is called, which applies yaw (`cam->rot.y -= delta_x * SENSITIVITY`) and pitch (`cam->rot.x += delta_y * SENSITIVITY`). Yaw wraps to $[-\pi, \pi]$ and pitch is clamped to $\pm\text{MAX_PITCH} \approx 88.2^\circ$ to prevent gimbal lock at zenith. Sensitivity is `0.003` and roll via Q/E is applied in the rotation handler, not from mouse. Mouse focus is toggled via `K`. When focused, the pointer is confined to the window using the XTEST extension (see build system notes on `local_xtst` for campus machines).

---

## BVH Debug Controls

The BVH debug system (`params_hooks1.c`, `params_hooks3.c`) provides real-time visualization of the acceleration structure. Pressing `V` toggles the debug overlay on and off. When enabled, the Up/Down keys adjust `params.bvh_depth` (-1 = max depth, 0..max_depth = specific depth). The Left/Right keys switch between BVH shapes (0: Sphere BVH, 1: AABB BVH with SAH, 2: OBB BVH with PCA). The `C` key cycles the heat map color palette offset through indices 0-9. The CPU-side `debug_rasterize_bvh()` rasterizes bounding boxes at the currently selected depth level using the camera projection (`project_point()`). Colors are either the heat map palette or a simple white outline depending on configuration.

*Animated GIF showing the BVH debug overlay cycling through different depth levels and bounding box shapes.*

---

## UI Mode Toggle (M key)

The `ui_mode()` function in `params_hooks2.c` cycles through three states using `ui_mode = (ui_mode + 1) % 3`. **Full UI** (mode 0) shows the left panel (scene list + editor), render switch, and on-display info. **Minimal** (mode 1) shows only render switch icons at top-right with `lpannel_toggle = false`. **Hidden** (mode 2) hides all UI with `ui_toggle = false` (body not rendered). When switching back to Full UI from Minimal, the render switch position is recalculated to account for the left panel width.