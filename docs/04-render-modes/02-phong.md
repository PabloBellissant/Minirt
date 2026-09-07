# Phong Shading (Index 1)

Phong shading computes per-pixel color using the **Phong reflection model** with ambient, diffuse, specular, emissive, and shadow-ray components. It runs as a GPU (OpenCL) kernel using progressive accumulation.

![Phong shading screenshot](../assets/img/phong-42.png)
*Screenshot of Phong mode showing ambient, diffuse, and specular lighting on a scene.*

## The Phong Reflection Model

The final color at a surface point is:

$$I = I_{\text{ambient}} + \sum_{i}(I_{\text{diffuse},i} + I_{\text{specular},i}) + I_{\text{emissive}}$$

Each term is computed per light source. The ambient component is a constant $k_d \cdot \text{ambient}$ applied before the light loop, where `ambient` is the scene ambient light and $k_d$ is the sampled diffuse albedo.

### Diffuse Term (Lambertian)

For each light $i$, the diffuse contribution uses **Lambert's cosine law**: $I_{\text{diffuse}} = k_d \cdot I_{\text{light}} \cdot \max(0, \mathbf{L} \cdot \mathbf{N})$, where $k_d$ is the diffuse albedo (from material texture), $I_{\text{light}}$ is the received light color (light rgb times shadow test), $\mathbf{L}$ is the normalized direction to light $i$, and $\mathbf{N}$ is the surface normal (from normal map if present). This is implemented in `get_phong_diffuse()`.

### Specular Term (Blinn-Phong)

The specular highlight is computed from the **reflected light direction**: $\mathbf{R} = 2(\mathbf{L} \cdot \mathbf{N})\mathbf{N} - \mathbf{L}$, with $I_{\text{specular}} = k_s \cdot (\mathbf{R} \cdot \mathbf{V})^{n_s} \cdot I_{\text{light}}$. Here $k_s$ is the specular intensity, $n_s$ is the shininess exponent, $\mathbf{V}$ is the direction to camera (view vector), and $\mathbf{R}$ is the reflection of the incident light direction. This is implemented in `get_specular()`.

### Shadow Rays

Before computing diffuse and specular contributions for a light, a **shadow ray** is cast from the hit point toward the light source using `get_color_through()`. If it hits an occluding object closer than the light distance, the light contribution is blocked. Otherwise, the full light color is returned.

### Emissive Term

After the light loop, the material's emissive color is added via `color += hit_data->ke`, allowing self-illuminating materials.
