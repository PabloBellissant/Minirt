# PBR (Index 2)

Physically-Based Rendering (PBR) extends the Phong model with **Fresnel reflectance**, **microfacet glossy factor**, **multi-bounce reflection/refraction**, and **through-power attenuation**. It uses a recursion loop with a fixed maximum bounce count.

![PBR rendering screenshot](../assets/img/showcase-render3.png)
*Screenshot of PBR mode showing Fresnel reflections, glossy reflections, and skybox environment mapping.*

## Fresnel and Reflectivity

The PBR kernel uses Fresnel reflectance (Schlick approximation with F0 computed from IOR and metalness) and a glossy factor modulated by roughness. The full F0 calculation, Schlick formula, and glossy factor derivation are documented in [08-materials-and-textures.md](../08-materials-and-textures.md).

## Reflection vs. Refraction

The `sample_refract()` function determines whether the ray **reflects** or **refracts** based on `hit_data.opacity`. When `random <= opacity`, the ray bounces off the surface using the law of reflection: $\mathbf{R} = \mathbf{D} - 2(\mathbf{D}\cdot\mathbf{N})\mathbf{N}$. When `random > opacity`, the ray passes through the material using **Snell's law** via `vec3_refract()`, where $\eta = \eta_1 / \eta_2$ (ratio of refractive indices). Total internal reflection is detected when the squared cosine term becomes negative.

## Bounce Loop

The PBR kernel fires up to `MAX_BOUNCE` (4) bounces per primary ray. Starting with `through_power = (1, 1, 1)`, each bounce computes Phong shading at the hit point, multiplies by $(1 - r) \cdot P$, and accumulates into the pixel color. `through_power` is then multiplied by `reflectivity` so that after $n$ bounces, the effective contribution is $P = \prod_{i} r_i$, which naturally dims deeper reflections. The ray is updated (origin at hit point, direction reflected or refracted) and the loop continues. When a ray misses all geometry and hits the skybox, `accumulated_color += draw_skybox(...) * through_power` and the loop breaks.

## Material Properties

| Property | Source | Used For |
|---|---|---|
| kd | Diffuse texture / material | Diffuse color |
| normal | Normal map (tangent-space) | Perturbed shading normal |
| ks | Material specular color | F0 metallic blend |
| ke | Material emissive | Emissive addition |
| metalness | Gray-level texture | F0 dielectric/metal blend |
| roughness | Gray-level texture | Glossy factor |
| opacity | Gray-level texture | Reflect/refract decision |
| ni (IOR) | Material IOR | Snell's law (refraction) |
