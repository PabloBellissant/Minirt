# Phong Shading (Index 1)

Phong shading computes per-pixel color using the **Phong reflection model** with ambient, diffuse, specular, emissive, and shadow-ray components. It runs as a GPU (OpenCL) kernel using progressive accumulation.

![Phong shading screenshot](../assets/img/showcase-render1.png)
*Screenshot of Phong mode showing ambient, diffuse, and specular lighting on a scene.*

## The Phong Reflection Model

The final color at a surface point is:

I = I_ambient + sum(I_diffuse_i + I_specular_i) + I_emissive

Each term is computed per light source. The ambient component is a constant `ambient * hit_data->kd` applied before the light loop, where `ambient` is the scene ambient light and `kd` is the sampled diffuse albedo.

### Diffuse Term (Lambertian)

For each light i, the diffuse contribution uses **Lambert's cosine law**: `I_diffuse = kd * I_light * max(0, L.N)`, where `kd` is the diffuse albedo (from material texture), `I_light` is the received light color (light rgb times shadow test), `L` is the normalized direction to light i, and `N` is the surface normal (from normal map if present). This is implemented in `get_phong_diffuse()`.

### Specular Term (Blinn-Phong)

The specular highlight is computed from the **reflected light direction**: `R = 2*(L.N)*N - L`, with `I_specular = ks * (R.V)^ns * I_light`. Here `ks` is the specular intensity, `ns` is the shininess exponent, `V` is the direction to camera (view vector), and `R` is the reflection of the incident light direction. This is implemented in `get_specular()`.

### Shadow Rays

Before computing diffuse and specular contributions for a light, a **shadow ray** is cast from the hit point toward the light source using `get_color_through()`. If it hits an occluding object closer than the light distance, the light contribution is blocked. Otherwise, the full light color is returned.

### Emissive Term

After the light loop, the material's emissive color is added via `color += hit_data->ke`, allowing self-illuminating materials.
