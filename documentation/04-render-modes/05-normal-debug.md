# Render Mode: Normal Debug (Mode 4)

Normal debug mode visualizes the surface normals of scene geometry as colors.
This is a diagnostic mode for checking normal map correctness, geometry
orientation, and vertex normal interpolation on triangle meshes.

---

## 1. Mapping Normals to Colors

Surface normals are unit vectors in the range $[-1, 1]$ per component. The
kernel maps each component to $[0, 1]$ using:

$$C = N \times 0.5 + 0.5$$

Where $N$ is the surface normal at the hit point and $C$ is the output color.

In component form:

$$R = N_x \times 0.5 + 0.5$$
$$G = N_y \times 0.5 + 0.5$$
$$B = N_z \times 0.5 + 0.5$$

### 1.1. Color Legend

| Normal Direction | RGB Color | Visual |
|---|---|---|
| (+X, 0, 0) Right | (1.0, 0.5, 0.5) | Red |
| (−X, 0, 0) Left | (0.0, 0.5, 0.5) | Cyan |
| (0, +Y, 0) Up | (0.5, 1.0, 0.5) | Green |
| (0, −Y, 0) Down | (0.5, 0.0, 0.5) | Magenta |
| (0, 0, +Z) Toward viewer | (0.5, 0.5, 1.0) | Blue |
| (0, 0, −Z) Away from viewer | (0.5, 0.5, 0.0) | Yellow |

---

## 2. Which Normal is Visualized

The normal displayed depends on the surface at the hit point:

- **Spheres**: Geometric normal (radial from sphere center to hit point)
- **Planes**: Plane normal (constant per plane)
- **Triangles**: Interpolated vertex normal using barycentric coordinates:
  $$N = N_0 \cdot \text{bary.x} + N_1 \cdot \text{bary.y} + N_2 \cdot \text{bary.z}$$

If the material has a **normal map** (`map_bump`), the perturbed normal from
the texture is used instead of the geometric normal.

---

## 3. Kernel Flow

```
normal_debug_kernel(pixel_x, pixel_y):
    1. Generate camera ray
    2. Trace BVH → nearest hit
    3. If no hit:
         return background / skybox color
    4. Sample surface:
       - Get geometric or interpolated normal
       - If normal map exists: perturb normal via TBN transform
    5. Ensure normal faces camera: if dot(N, ray_dir) > 0, flip N
    6. C = N × 0.5 + 0.5
    7. accu[pixel] += C
```

The normal is always oriented toward the camera (front-facing) to avoid
ambiguity in the color mapping.

---

## 4. Use Cases

- **Verifying normal maps**: Ensure tangent-space normal maps are correctly
  oriented (blue-ish dominant color = mostly outward-facing normals)
- **Checking triangle orientation**: Flipped triangles appear with unexpected
  colors (e.g., red where it should be green)
- **Debugging BVH culling**: Missing geometry appears as skybox; incorrectly
  culled triangles show as background
- **Assessing mesh quality**: Smooth color gradients across triangles indicate
  well-interpolated vertex normals; flat-shaded triangles show no interpolation

---

## 5. Performance

Normal debug mode is extremely fast — it requires only:

- 1 primary ray cast
- 1 normal lookup (no shading, no shadow rays, no bounces)
- 1 color mapping

Performance is comparable to or faster than Phong mode.