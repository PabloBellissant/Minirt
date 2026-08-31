# Render Mode: Wireframe (Mode 0)

Wireframe mode is a **CPU rasterization debug view** that visualizes the scene's
geometric structure without ray tracing. It is the only render mode that does
not use OpenCL; instead it draws directly using minilibx rasterization
primitives.

---

## 1. Purpose

Wireframe mode helps developers and users understand:

- **BVH structure** — the bounding box hierarchy is drawn as outlines, showing
  how space is partitioned
- **Object placement** — spheres, planes, and triangle meshes are outlined
- **Light positions** — point lights are drawn as circles
- **Depth ordering** — objects are colored by depth using a rainbow palette

---

## 2. What is Drawn

### 2.1. BVH Boxes

When BVH debug mode is active (`bvh_debug` flag), the function
`rasterize_bvh()` traverses the BVH tree and draws each node's axis-aligned
bounding box as a set of 12 line segments (the edges of the cuboid).

- BVH depth filtering: only nodes at `bvh_depth` or shallower are drawn
- Boxes are colored using the rainbow palette based on tree depth

### 2.2. Object Outlines

Each primitive type has its own outline function:

- **Spheres** (`rasterize_sphere_outline`): The sphere's silhouette as seen from
  the camera is projected to screen space. The silhouette is a circle whose
  radius depends on the sphere's diameter and distance from the camera.

- **Triangles** (`rasterize_triangle_outline`): Each triangle's three edges are
  projected and drawn as line segments.

- **Planes** (`rasterize_plane_outline`): The plane is represented by drawing a
  grid or outline at the plane's position, oriented along its tangent and
  bitangent vectors.

### 2.3. Light Circles

Each point light is drawn as a yellow circle (`rasterize_light_outline`). The
circle is centered at the projected light position with a fixed radius in
screen space.

---

## 3. 3D to Screen Projection

### 3.1. Point Projection

Given a 3D world point $P$, the camera view matrix projects it to screen
coordinates:

```
P_view = P - camera.pos
x_screen = dot(P_view, camera_right)
y_screen = dot(P_view, camera_up)
z_screen = dot(P_view, camera_forward)

screen_x = (x_screen / z_screen) * focal_length + screen_width / 2
screen_y = -(y_screen / z_screen) * focal_length + screen_height / 2
```

where `focal_length = screen_width / (2 * tan(fov / 2))`.

Only points with `z_screen > 0` (in front of the camera) are drawn.

### 3.2. Line Rasterization

Lines are rasterized using Bresenham-like integer stepping in the minilibx
image buffer. Each pixel along the line segment between two projected points
gets the current color.

---

## 4. Rainbow Color Palette

The `float_to_rainbow()` function maps a depth value `t` (0.0 – 1.0) to a color
along a rainbow gradient:

$$C(t) = \text{lerp}(P_i, P_{i+1}, \text{smoothstep}(t))$$

where $P_i$ are palette stops at:

| Stop | Position | Color |
|---|---|---|
| 0 | 0.00 | Red |
| 1 | 0.17 | Orange |
| 2 | 0.33 | Yellow |
| 3 | 0.50 | Green |
| 4 | 0.67 | Cyan |
| 5 | 0.83 | Blue |
| 6 | 1.00 | Violet |

**smoothstep** is the cubic Hermite interpolation:

$$\text{smoothstep}(t) = 3t^2 - 2t^3$$

applied to the normalized position within each segment.

Objects are colored based on their distance from the camera: nearer objects
tend toward red, farther objects toward violet.

---

## 5. BVH Debug Overlay

When `bvh_debug` is enabled in a non-wireframe mode, the wireframe BVH outlines
are **overlaid** on top of the ray-traced image. This is useful for
understanding which BVH nodes are being traversed:

- `bvh_depth` (int): Only draw nodes at this depth level. `-1` = draw all.
- `bvh_color_offset` (int): Cycle through color palettes by shifting the hue
  mapping.
- `bvh_mode` (0/1): Switch between sphere BVH (mode 0) and AABB BVH (mode 1)
  visualization.

---

## 6. Performance Characteristics

Wireframe mode is **instantaneous** because it uses CPU rasterization with no
ray tracing overhead. It is primarily a debugging and scene inspection tool,
not intended for final rendering.

---

## 7. Code Path

```
wireframe_render()
├─ rasterize_bvh()          — traverse BVH, draw all/nodes
│   └─ rasterize_cuboid()   — draw 12 edges of one AABB
├─ rasterize_sphere_outline() — project + draw sphere silhouettes
├─ rasterize_triangle_outline() — project + draw triangle edges
├─ rasterize_plane_outline()  — project + draw plane representation
└─ rasterize_light_outline() — draw yellow circles at light positions
```

All functions write directly to the minilibx image buffer (`t_img_data`).