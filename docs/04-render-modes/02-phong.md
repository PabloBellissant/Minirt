# Phong Shading (Index 1)

Phong shading computes per-pixel color using the **Phong reflection model** with ambient, diffuse, specular, emissive, and shadow-ray components. It is a GPU (OpenCL) kernel using progressive accumulation.

## Source Files

- `shader/phong.cl` — kernel entry point
- `shader/phong_shading.cl` — Phong shading functions

## Kernel Flow

```
phong() kernel (per pixel)
  ├─ calc_ray(&cam, pos, &rng)         — generate camera ray
  ├─ hit_register_gpu(&ray, &objects)  — BVH traversal → nearest hit
  ├─ if hit:
  │    ├─ sample_materials(&hit, ...)  — fetch textures, compute normals
  │    └─ phong_shading(&hit_data, ...) — compute accumulated color
  │         └─ img[pixel] += hit_data.kd
  └─ else:
       └─ img[pixel] = 0
```

## The Phong Reflection Model

The final color at a surface point is:

$$
I = I_{\text{ambient}} + \sum_{i=0}^{n} \left( I_{\text{diffuse},i} + I_{\text{specular},i} \right) + I_{\text{emissive}}
$$

Where each term is computed per light source.

### Ambient Term

The ambient component is a constant `(ambient * hit_data->kd)` applied before iterating lights:

```c
color = ambient;
color *= hit_data->kd;
```

Where `ambient` is the scene ambient light (`rgb3`) and `hit_data->kd` is the sampled diffuse albedo from the material's texture.

### Diffuse Term (Lambertian)

For each light $i$, the diffuse contribution uses **Lambert's cosine law**:

$$
I_{\text{diffuse},i} = k_d \cdot I_{\text{light},i} \cdot \max(0, \hat{L}_i \cdot \hat{N})
$$

Where:
- $k_d$ = diffuse albedo (from material texture)
- $I_{\text{light},i}$ = received light color (light rgb × shadow test)
- $\hat{L}_i$ = normalized direction to light $i$
- $\hat{N}$ = surface normal (from normal map if present)

Implemented in `get_phong_diffuse()`:

```c
rgb3 get_phong_diffuse(rgb3 l_m, rgb3 i_d, rgb3 n, rgb3 k_d)
{
    if (dot(l_m, n) <= 0) return (rgb3)(0, 0, 0);
    return ((k_d * i_d) * dot(l_m, n));
}
```

### Specular Term (Blinn-Phong)

The specular highlight is computed from the **reflected light direction**:

$$
\hat{R}_i = 2(\hat{L}_i \cdot \hat{N})\hat{N} - \hat{L}_i
$$

$$
I_{\text{specular},i} = k_s \cdot (\hat{R}_i \cdot \hat{V})^{n_s} \cdot I_{\text{light},i}
$$

Where:
- $k_s$ = specular intensity (from material)
- $n_s$ = shininess exponent (from material)
- $\hat{V}$ = direction to camera (view vector)
- $\hat{R}_i$ = reflection of incident light direction

Implemented in `get_specular()`:

```c
rgb3 get_specular(rgb3 r_m, rgb3 v, rgb3 k_s, float n_s)
{
    surface_faces_camera = dot(r_m, v);
    if (surface_faces_camera <= 0) return (rgb3)(0, 0, 0);
    surface_faces_camera = pow(surface_faces_camera, n_s);
    return (k_s * surface_faces_camera);
}
```

### Shadow Rays

Before computing diffuse and specular contributions for a light, a **shadow ray** is cast from the hit point toward the light source using `get_color_through()`:

```c
receive_color = objects->lights[i].rgb
    * get_color_through(hit_point, dir_to_light, objects,
                        dot(hit_point - light_pos, hit_point - light_pos),
                        bvh_type);
```

`get_color_through()` casts a secondary ray from the hit point toward the light. If it hits an occluding object closer than the light distance, the light contribution is blocked (returns `(0,0,0)`). Otherwise, the full light color is returned.

### Emissive Term

After the light loop, the material's emissive color is added:

```c
color += hit_data->ke;
```

This allows self-illuminating materials.

## Material Sampling

`sample_materials()` in `shader/sample_materials.cl` fetches per-pixel material properties from textures:

- **kd**: Diffuse color (from texture or material default)
- **normal**: Surface normal with normal mapping (tangent-space transform)
- **ks**: Specular intensity
- **ke**: Emissive color
- **ns**: Shininess exponent
- **ambient**: Ambient occlusion factor (from gray-level texture)

The final color is clamped to $[0, 1]$:

```c
color = clamp(color, 0.0f, 1.0f);
```