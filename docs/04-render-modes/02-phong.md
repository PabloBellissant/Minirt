# Phong Shading (Index 1)

Phong shading computes per-pixel color using the **Phong reflection model** with ambient, diffuse, specular, emissive, and shadow-ray components. It is a GPU (OpenCL) kernel using progressive accumulation.

## Source Files

The source files are `shader/phong.cl` (the kernel entry point) and `shader/phong_shading.cl` (the Phong shading functions).

## Kernel Flow

```
phong() kernel (per pixel)
  +-- calc_ray(&cam, pos, &rng)         - generate camera ray
  +-- hit_register_gpu(&ray, &objects)  - BVH traversal -> nearest hit
  +-- if hit:
  |    +-- sample_materials(&hit, ...)  - fetch textures, compute normals
  |    +-- phong_shading(&hit_data, ...) - compute accumulated color
  |         +-- img[pixel] += hit_data.kd
  +-- else:
       +-- img[pixel] = 0
```

![Phong rendering screenshot](docs/assets/phong-mode.png)
*Screenshot of Phong mode showing ambient, diffuse, and specular lighting on a scene.*

## The Phong Reflection Model

The final color at a surface point is:

$$I = I_{\text{ambient}} + \sum_{i=0}^{n} \left( I_{\text{diffuse},i} + I_{\text{specular},i} \right) + I_{\text{emissive}}$$

Each term is computed per light source.

### Ambient Term

The ambient component is a constant `(ambient * hit_data->kd)` applied before iterating lights, where `ambient` is the scene ambient light (`rgb3`) and `hit_data->kd` is the sampled diffuse albedo from the material's texture.

### Diffuse Term (Lambertian)

For each light $i$, the diffuse contribution uses **Lambert's cosine law**: $I_{\text{diffuse},i} = k_d \cdot I_{\text{light},i} \cdot \max(0, \hat{L}_i \cdot \hat{N})$, where $k_d$ is the diffuse albedo (from material texture), $I_{\text{light},i}$ is the received light color (light rgb times shadow test), $\hat{L}_i$ is the normalized direction to light $i$, and $\hat{N}$ is the surface normal (from normal map if present). This is implemented in `get_phong_diffuse()`.

### Specular Term (Blinn-Phong)

The specular highlight is computed from the **reflected light direction**: $\hat{R}_i = 2(\hat{L}_i \cdot \hat{N})\hat{N} - \hat{L}_i$, with $I_{\text{specular},i} = k_s \cdot (\hat{R}_i \cdot \hat{V})^{n_s} \cdot I_{\text{light},i}$. Here $k_s$ is the specular intensity, $n_s$ is the shininess exponent, $\hat{V}$ is the direction to camera (view vector), and $\hat{R}_i$ is the reflection of the incident light direction. This is implemented in `get_specular()`.

### Shadow Rays

Before computing diffuse and specular contributions for a light, a **shadow ray** is cast from the hit point toward the light source using `get_color_through()`. This function casts a secondary ray from the hit point toward the light. If it hits an occluding object closer than the light distance, the light contribution is blocked (returns `(0,0,0)`). Otherwise, the full light color is returned.

### Emissive Term

After the light loop, the material's emissive color is added via `color += hit_data->ke`, allowing self-illuminating materials.

## Material Sampling

`sample_materials()` in `shader/sample_materials.cl` fetches per-pixel material properties from textures: **kd** (diffuse color from texture or material default), **normal** (surface normal with normal mapping via tangent-space transform), **ks** (specular intensity), **ke** (emissive color), **ns** (shininess exponent), and **ambient** (ambient occlusion factor from gray-level texture). The final color is clamped to $[0, 1]$.