# Camera Model and Interactive Controls

## Overview

miniRT implements a 6-degree-of-freedom (6-DOF) camera with Euler angle
rotation, a configurable field-of-view viewport, and depth-of-field via a
thin lens model. The camera state is stored in `t_camera` (host) and
`t_camera_gpu` (device).

---

## Euler Angle Rotation

The camera orientation is defined by three Euler angles stored in `cam.rot`:

| Component | Axis | Range | Description |
|-----------|------|-------|-------------|
| `rot.x` | Pitch (X-axis) | $[-\frac{\pi}{2}, \frac{\pi}{2}]$ | Vertical look angle (up/down) |
| `rot.y` | Yaw (Y-axis) | $[-\pi, \pi]$ | Horizontal look angle (left/right) |
| `rot.z` | Roll (Z-axis) | $[-\pi, \pi]$ | Roll angle (tilt head) |

### Basis Vector Computation

From `camera_utils.c`, `apply_yaw_and_pitch()`:

**Forward vector** (where the camera points):

$$
\begin{aligned}
\text{forward}_x &= \sin(\text{yaw}) \cdot \cos(\text{pitch}) \\
\text{forward}_y &= \sin(\text{pitch}) \\
\text{forward}_z &= \cos(\text{yaw}) \cdot \cos(\text{pitch})
\end{aligned}
$$

**Temporary right and up** (before roll):

$$
\begin{aligned}
\text{right}_\text{temp} &= (\cos(\text{yaw}),\; 0,\; -\sin(\text{yaw})) \\
\text{up}_\text{temp} &= (-\sin(\text{yaw}) \cdot \sin(\text{pitch}),\; \cos(\text{pitch}),\; \cos(\text{yaw}) \cdot -\sin(\text{pitch}))
\end{aligned}
$$

**Final right and up** (after applying roll via Rodrigues-style rotation):

$$
\begin{aligned}
\text{right} &= \text{right}_\text{temp} \cdot \cos(\text{roll}) - \text{up}_\text{temp} \cdot \sin(\text{roll}) \\
\text{up} &= \text{right}_\text{temp} \cdot \sin(\text{roll}) + \text{up}_\text{temp} \cdot \cos(\text{roll})
\end{aligned}
$$

This yields a full orthonormal basis: $\{\text{right}, \text{up}, \text{forward}\}$.

---

## Viewport Setup

The viewport defines the rectangular region in world space corresponding to
the screen pixels. From `camera_utils.c`, `fill_camera()`:

### Viewport Height

$$
\text{viewport}_{\text{height}} = 2 \cdot \tan\left(\frac{\text{FOV} \cdot \pi}{180 \cdot 2}\right)
$$

Where FOV is the vertical field of view in degrees (from the `.rt` scene
file). For a typical FOV of 60°:

$$
\text{viewport}_{\text{height}} = 2 \cdot \tan(30^\circ) \approx 1.1547
$$

### Viewport Width

$$
\text{viewport}_{\text{width}} = \text{viewport}_{\text{height}} \cdot \frac{\text{screen}_{\text{width}}}{\text{screen}_{\text{height}}}
$$

### Pixel Dimensions

The pixel delta vectors define the per-pixel step in world space:

$$
\begin{aligned}
\text{pixel\_delta\_u} &= \frac{\text{camera\_right} \cdot \text{viewport}_{\text{width}}}{\text{screen}_{\text{width}}} \\
\text{pixel\_delta\_v} &= \frac{-\text{camera\_up} \cdot \text{viewport}_{\text{height}}}{\text{screen}_{\text{height}}}
\end{aligned}
$$

### Pixel 00 Location (Top-Left)

The world-space position of the top-left pixel center:

$$
\begin{aligned}
\text{viewport\_upper\_left} &= \text{camera\_pos} - \text{forward} - \frac{u}{2} - \frac{v}{2} \\
\text{pixel00\_loc} &= \text{viewport\_upper\_left} + \frac{\text{pixel\_delta\_u} + \text{pixel\_delta\_v}}{2}
\end{aligned}
$$

Where $u = \text{camera\_right} \cdot \text{viewport}_{\text{width}}$ and
$v = \text{camera\_up} \cdot (-\text{viewport}_{\text{height}})$.

---

## Depth of Field (Thin Lens Model)

DOF simulates a real camera with a finite aperture. Instead of firing rays
from a single point, rays originate from random positions on a disk centered
on the camera position, then pass through the focal point.

### Focal Point

The focal point is the point in world space at exactly `focus_dist`
units along the initial ray direction:

```math
\text{focal\_point} = \text{camera\_pos} + \text{ray\_dir} \cdot \text{focus\_dist}
```

### Lens Sampling

A random point on the lens disk is computed:

$$
\text{disk} = \text{random\_in\_unit\_disk}() \cdot r_{\text{lens}}
$$

Where `random_in_unit_disk()`:

$$
\begin{aligned}
r &= \sqrt{\text{random}()} \\
\theta &= 2\pi \cdot \text{random}() \\
\text{disk} &= (r \cdot \cos(\theta),\; r \cdot \sin(\theta))
\end{aligned}
$$

### Lens Offset and Final Ray

The lens offset translates the camera origin:

```math
\text{lens\_offset} = \text{camera\_right} \cdot \text{disk}_x + \text{camera\_up} \cdot \text{disk}_y
```

Then the final ray is:

```math
\begin{aligned}
\text{ray.origin} &= \text{camera\_pos} + \text{lens\_offset} \\
\text{ray.dir} &= \text{normalize}(\text{focal\_point} - \text{ray.origin})
\end{aligned}
```

This ensures all rays pass through the focal plane, creating the DOF blur
effect for objects not at the focal distance.

### DOF Parameters

| Parameter | Default | Description |
|-----------|---------|-------------|
| `lens_radius` | 0.0 (varies per scene) | Aperture size — larger = more blur |
| `focus_dist` | 1.0 (varies per scene) | Distance to the focal plane |

Interactive controls:
- **T/G:** Increase/decrease `focus_dist` (×1.05/÷1.05)
- **Y/H:** Increase/decrease `lens_radius` (×1.05/÷1.05)

---

## Keyboard Controls

### Movement

| Key | Action | Axis |
|-----|--------|------|
| **W** | Move forward | Horizontal plane (XZ) |
| **S** | Move backward | Horizontal plane (XZ) |
| **A** | Move left (strafe) | Horizontal plane (XZ) |
| **D** | Move right (strafe) | Horizontal plane (XZ) |
| **Space** | Move up | Y-axis |
| **Shift** | Move down | Y-axis |
| **Q** | Roll left (counter-clockwise) | Z-axis |
| **E** | Roll right (clockwise) | Z-axis |

### Render Modes

| Key | Mode | Description |
|-----|------|-------------|
| **1** | Wireframe | CPU rasterized debug view |
| **2** | Phong | GPU Phong shading |
| **3** | PBR | GPU physically based rendering |
| **4** | Monte Carlo | GPU path tracing with accumulation |
| **-** | Normal debug | GPU normal visualization |
| **=** | Heat map | GPU BVH depth heat map |

### Special Controls

| Key | Action |
|-----|--------|
| **K** | Toggle mouse focus (enable/disable look control) |
| **V** | Toggle BVH debug overlay |
| **C** | Cycle BVH color offset (next palette) |
| **↑/↓** | Increase/decrease BVH depth level |
| **←/→** | Switch BVH mode (sphere/AABB) |
| **T/G** | Increase/decrease focus distance |
| **Y/H** | Increase/decrease lens radius |
| **F12** | Export current frame to PPM |
| **F11** | Export scene to .rt file |

---

## Mouse Look

Camera rotation is controlled by mouse movement when mouse focus is active
(window focused).

### Sensitivity

```c
#define SENSITIVITY 0.001f
```

Mouse delta (in pixels) is multiplied by sensitivity:

```math
\begin{aligned}
\text{yaw} &\mathrel{-}= \Delta x \cdot 0.001 \\
\text{pitch} &\mathrel{+}= \Delta y \cdot 0.001
\end{aligned}
```

### Pitch Clamping

Pitch is clamped to prevent the camera from flipping:

```c
#define MAX_PITCH 1.53938043117523193F  // ≈ 88.2°
```

This limits the vertical look range to just under $\pm 90^\circ$ (gimbal lock
prevention).

### Yaw Wrapping

Yaw wraps at $\pm \pi$:

```c
if (data->scene.camera.rot.y < -M_PI)
    data->scene.camera.rot.y += M_PI * 2;
else if (data->scene.camera.rot.y > M_PI)
    data->scene.camera.rot.y -= M_PI * 2;
```

### Roll Sensitivity

Roll (Q/E keys) uses a separate, higher sensitivity:

```c
#define ROLL_SENSITIVITY 0.01f
```

---

## Movement Speed

### Speed Formula

```c
const float step = MOVE_SPEED * (1 + ctrl) * delta_time;
```

Where:

| Component | Typical Value | Description |
|-----------|---------------|-------------|
| `MOVE_SPEED` | 3.0 | Base movement speed (world units/sec) |
| `ctrl` | 0 or 1 | Ctrl key modifier (1 = 2× speed) |
| `delta_time` | ~0.016 (60 FPS) | Time since last frame in seconds |

### Effect of Ctrl

When Ctrl is held, `ctrl = 1`, doubling the speed:

$$
\text{step} = 3 \cdot (1 + 1) \cdot \Delta t = 6 \cdot \Delta t
$$

Without Ctrl:

$$
\text{step} = 3 \cdot (1 + 0) \cdot \Delta t = 3 \cdot \Delta t
$$

### Horizontal Movement

WASD movement uses the horizontal projection of the camera basis (yaw only,
pitch ignored):

```math
\begin{aligned}
\text{forward}_\text{horizontal} &= (-\sin(\text{yaw}),\; 0,\; -\cos(\text{yaw})) \\
\text{right}_\text{horizontal} &= (\cos(\text{yaw}),\; 0,\; -\sin(\text{yaw}))
\end{aligned}
```

Vertical movement (Space/Shift) is direct Y-axis translation.

---

## BVH Debug Controls

When BVH debug is enabled (V key to toggle), additional controls are
available:

| Key | Effect |
|-----|--------|
| **↑** | Decrease BVH depth (one level deeper) |
| **↓** | Increase BVH depth (one level shallower) |
| **←** | Switch to previous BVH mode (0=sphere, 1=AABB) |
| **→** | Switch to next BVH mode |
| **C** | Cycle through color palettes (increments `bvh_color_offset`) |

The BVH debug overlay rasterizes the BVH hierarchy as wireframe boxes on top
of the rendered image, color-coded by depth. Each palette provides different
gradient stops for visual distinction of tree levels. The `bvh_depth`
parameter controls which depth level to visualize (-1 = all levels).

---

## Camera Movement Flow (Per Frame)

```mermaid
graph TD
    A[loop()] --> B[handle_camera_move]
    B --> C{keys.forward?}
    C -->|Yes| D[adjust_cam +step]
    C -->|No| E{keys.backward?}
    E -->|Yes| F[adjust_cam -step]
    E -->|No| G{keys.right?}
    G -->|Yes| H[adjust_cam right +step]
    G -->|No| I{keys.left?}
    I -->|Yes| J[adjust_cam right -step]
    I -->|No| K{keys.upward?}
    K -->|Yes| L[pos.y += step]
    K -->|No| M{shift?}
    M -->|Yes| N[pos.y -= step]
    M -->|No| O[check mouse/roll]
    O --> P{roll_left?}
    P -->|Yes| Q[rot.z -= 0.01]
    P -->|No| R{roll_right?}
    R -->|Yes| S[rot.z += 0.01]
    R -->|No| T[mouse focus?]
    T -->|Yes| U[handle_camera_rotation]
    U --> V{delta_x/delta_y}
    V --> W[rot.y -= delta_x × 0.001]
    V --> X[rot.x += delta_y × 0.001]
    X --> Y[clamp pitch to ±1.539]
```