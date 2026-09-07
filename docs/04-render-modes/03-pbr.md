# PBR (Index 2)

Physically-Based Rendering (PBR) extends the Phong model with **Fresnel reflectance**, **microfacet glossy factor**, **reflection/refraction bounce loop**, and **through-power attenuation**. It uses a multi-bounce recursion with a fixed maximum bounce count.

## Source Files

The source is split across two files: `shader/pbr.cl` provides the kernel entry point, while `shader/sample_materials.cl` handles F0 computation, Schlick Fresnel, and refraction.

## Kernel Flow

```
pbr() kernel (per pixel)
  +-- calc_ray(&cam, pos, &rng)
  +-- accumulated_color = (0,0,0)
  +-- through_power = (1,1,1)
  +-- bounce = 0
  +-- while (bounce < MAX_BOUNCE):
       +-- hit_register_gpu(&ray, &objects, bvh_type)
       +-- if hit:
       |    +-- sample_refract(&hit, ...)   - sample material, decide reflect/refract
       |    +-- accumulated_color += phong_shading(...) * (1 - reflectivity) * through_power
       |    +-- through_power *= reflectivity
       |    +-- ray updated (origin = hit_point, dir = reflect or refract)
       |    +-- bounce++
       +-- else:
            +-- accumulated_color += draw_skybox(...) * through_power
            +-- break
  +-- img[pixel] += accumulated_color
```

![PBR rendering screenshot](../assets/img/bvh-volume-theme2.png)
*Screenshot of PBR mode showing Fresnel reflections, glossy reflections, and skybox environment mapping.*

## Fresnel and Reflectivity

The PBR kernel uses Fresnel reflectance (Schlick approximation with F0 computed from IOR and metalness) and a glossy factor modulated by roughness. The full F0 calculation, Schlick formula, and glossy factor derivation are documented in [08-materials-and-textures.md](../08-materials-and-textures.md).

## Reflection vs. Refraction

The `sample_refract()` function determines whether the ray **reflects** or **refracts** based on `hit_data.opacity`. When `random <= opacity`, the ray bounces off the surface using the law of reflection ($\hat{R} = \hat{D} - 2(\hat{D} \cdot \hat{N})\hat{N}$). When `random > opacity`, the ray passes through the material using **Snell's law** via `vec3_refract()`, where $\eta = \frac{\eta_1}{\eta_2}$ (ratio of refractive indices). Total internal reflection is detected when the squared cosine term becomes negative.

## Bounce Loop

The PBR kernel fires up to `MAX_BOUNCE` (4) bounces per primary ray. Bounce 0 computes the primary hit with Phong shading (diffuse + specular surface color) times `(1 - reflectivity) * through_power`, then `through_power *= reflectivity`. Each subsequent bounce follows the same pattern with further attenuation. When a ray misses all geometry and hits the skybox, `accumulated_color += skybox_color * through_power` and the loop breaks.

## Through-Power Attenuation

Starting at `(1, 1, 1)`, `through_power` accumulates the multiplicative reflectivity across bounces via `through_power *= hit_data.reflectivity`. After $n$ bounces, the effective contribution of the $n$th bounce is $\text{through_power} = \prod_{i=1}^{n} \text{reflectivity}_i$, which naturally dims deeper reflections.

## Skybox

When a ray misses all geometry, `draw_skybox()` samples the environment texture using the ray direction as UV coordinates. The skybox color is weighted by `through_power` so it participates in the multi-bounce energy transport.

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