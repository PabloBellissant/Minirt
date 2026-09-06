# Normal Debug Mode (Index 4)

Normal debug mode visualizes surface normals directly, mapping each normal vector component to a color channel.

## Source File

`shader/normal_debug.cl`

## Kernel

```c
__kernel void normal_debug(t_camera_gpu cam, __constant t_bvh_node_gpu *bvh,
    int bvh_type, __constant t_sphere_gpu *spheres,
    __constant t_triangle_gpu *triangles, __constant t_plane_gpu *planes,
    int planes_count, __global float3 *img,
    __constant uchar *textures, __constant t_mat_gpu *mats)
{
    // Generate ray, BVH traversal
    // If hit:
    t_hit_data hit_data = sample_materials(&hit, textures, mats, &ray);
    img[pixel] += hit_data.normal * 0.5f + 0.5f;

    // If miss:
    img[pixel] = 0;
}
```

## Normal Visualization Formula

The surface normal $\hat{N} = (N_x, N_y, N_z)$ is mapped to RGB colorspace as:

$$\text{color} =
\begin{pmatrix}
N_x \cdot 0.5 + 0.5 \\
N_y \cdot 0.5 + 0.5 \\
N_z \cdot 0.5 + 0.5
\end{pmatrix}$$

Since each normal component is in $[-1, 1]$, the mapping shifts it to $[0, 1]$. For example, +X (right) maps to pink/red, -X (left) maps to teal, +Y (up) maps to green, -Y (down) maps to purple, +Z (forward) maps to blue, and -Z (backward) maps to yellow. When a ray misses all geometry, the pixel is set to black $(0, 0, 0)$.

*Screenshot of normal debug mode showing surface normals mapped to RGB colors.*

## Key Details

The mode uses `sample_materials()` to get the **mapped normal** (after tangent-space normal map perturbation), not the raw geometric normal. This means normal map textures are visible in the debug view. It uses progressive accumulation with `img[pixel] += ...`, but since the normal is deterministic, the result stabilizes immediately with no stochastic component. Miss pixels remain black, clearly distinguishing background from geometry.