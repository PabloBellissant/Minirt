# PBR (Index 2)

Physically-Based Rendering (PBR) extends the Phong model with **Fresnel reflectance**, **microfacet glossy factor**, **reflection/refraction bounce loop**, and **through-power attenuation**. It uses a multi-bounce recursion with a fixed maximum bounce count.

## Source Files

- `shader/pbr.cl` — kernel entry point
- `shader/sample_materials.cl` — F0 computation, Schlick Fresnel, refraction

## Kernel Flow

```
pbr() kernel (per pixel)
  ├─ calc_ray(&cam, pos, &rng)
  ├─ accumulated_color = (0,0,0)
  ├─ through_power = (1,1,1)
  ├─ bounce = 0
  └─ while (bounce < MAX_BOUNCE):
       ├─ hit_register_gpu(&ray, &objects, bvh_type)
       ├─ if hit:
       │    ├─ sample_refract(&hit, ...)   — sample material, decide reflect/refract
       │    ├─ accumulated_color += phong_shading(...) * (1 - reflectivity) * through_power
       │    ├─ through_power *= reflectivity
       │    ├─ ray updated (origin = hit_point, dir = reflect or refract)
       │    └─ bounce++
       └─ else:
            ├─ accumulated_color += draw_skybox(...) * through_power
            └─ break
  └─ img[pixel] += accumulated_color
```

## Fresnel Reflectance — F0

The **base reflectivity at normal incidence** ($F_0$) combines metalness and IOR:

```c
rgb3 get_f0(float metalness, float ior, rgb3 ks)
{
    float no_metal = ((ior - 1.0f) / (ior + 1.0f));
    no_metal *= no_metal;
    return (mix((float3)no_metal, ks, metalness));
}
```

For dielectric materials ($\text{metalness} \approx 0$):

$$
F_0 = \left(\frac{\eta - 1}{\eta + 1}\right)^2
$$

For metallic materials ($\text{metalness} \approx 1$), $F_0$ blends toward the specular color $k_s$.

## Schlick Fresnel

The Fresnel term at grazing angles uses the **Schlick approximation**:

$$
F(\theta) = F_0 + (1 - F_0)(1 - \cos\theta)^5
$$

Where $\cos\theta = |\hat{R} \cdot \hat{N}|$ (absolute dot of incident ray and normal).

```c
cos_theta = fabs(dot(ray_dir, normal));
fresnel = (1 - F0) * (pow(1.0f - cos_theta, 5.0f));
fresnel += F0;
```

## Glossy Factor

The glossy (specular) factor incorporates the material's roughness:

```c
glossy_factor = 1.0f - (roughness * roughness);
specular = fresnel * glossy_factor;
```

The final **reflectivity** output to `hit_data.reflectivity` combines Fresnel and roughness into a single scalar (clamped to $[0,1]$):

```c
return (clamp(specular, 0.0f, 1.0f));
```

### Reflectivity Meaning

- **reflectivity = 1** → fully reflective (mirror), ray is reflected
- **reflectivity = 0** → fully diffuse/transmissive, ray is refracted
- Intermediate values → weighted combination

## Reflection vs. Refraction

The `sample_refract()` function determines whether the ray **reflects** or **refracts** based on `hit_data.opacity`:

```c
hit_data.opacity = fmax(hit_data.opacity, hit_data.reflectivity.x);
if (random > hit_data.opacity)
{
    refract(&ray->dir, hit, &hit_data, hit_data.ni);
    hit_data.reflectivity = 1 - hit_data.opacity;
}
else
{
    ray->dir = reflect(ray->dir, hit->normal);
}
```

- **Reflection**: When `random <= opacity`, the ray bounces off the surface using the law of reflection ($\hat{R} = \hat{D} - 2(\hat{D} \cdot \hat{N})\hat{N}$).
- **Refraction** (transmission): When `random > opacity`, the ray passes through the material using **Snell's law** via `vec3_refract()`:

```c
float3 vec3_refract(float3 ray_dir, float3 normal, float eta)
{
    float cosi = -dot(ray_dir, normal);
    float cost2 = 1.0f - eta * eta * (1.0f - cosi * cosi);
    if (cost2 < 0.0001f) return (0);  // total internal reflection
    float cost = sqrt(cost2);
    return normalize(ray_dir * eta + normal * (eta * cosi - cost));
}
```

Where $\eta = \frac{\eta_1}{\eta_2}$ (ratio of refractive indices).

## Bounce Loop

The PBR kernel fires up to `MAX_BOUNCE` (4) bounces per primary ray:

```
Bounce 0: Primary hit → Phong shade (diffuse + specular surface color)
         × (1 - reflectivity) × through_power
         through_power *= reflectivity
         Ray reflects or refracts

Bounce 1: Secondary hit → same calculation
         through_power attenuates further

... up to MAX_BOUNCE

Miss (skybox):
         accumulated_color += skybox_color × through_power
         break
```

Each bounce attenuates the **through_power** by the material's reflectivity, gradually reducing the contribution of deeper bounces.

## Through-Power Attenuation

Starting at `(1, 1, 1)`, `through_power` accumulates the multiplicative reflectivity across bounces:

```c
through_power *= hit_data.reflectivity;
```

After $n$ bounces, the effective contribution of the $n$th bounce is:

$$
\text{through\_power} = \prod_{i=1}^{n} \text{reflectivity}_i
$$

This naturally dims deeper reflections.

## Skybox

When a ray misses all geometry, `draw_skybox()` samples the environment texture using the ray direction as UV coordinates:

```c
float3 draw_skybox(t_hit_gpu *hit, __constant uchar *textures, t_texture_data skybox)
{
    x = (int)(hit->uv.x * (float)(skybox.width - 1));
    y = (int)(hit->uv.y * (float)(skybox.height - 1));
    offset = skybox.offset + y * (skybox.width * skybox.channels) + x * skybox.channels;
    // return RGB pixel
}
```

The skybox color is weighted by `through_power` so it participates in the multi-bounce energy transport.

## Material Properties (from `sample_materials.cl`)

| Property       | Source                     | Used For                |
|----------------|----------------------------|-------------------------|
| kd             | Diffuse texture / material | Diffuse color           |
| normal         | Normal map (tangent-space) | Perturbed shading normal |
| ks             | Material specular color    | F0 metallic blend       |
| ke             | Material emissive          | Emissive addition       |
| metalness      | Gray-level texture         | F0 dielectric/metal blend |
| roughness      | Gray-level texture         | Glossy factor           |
| opacity        | Gray-level texture         | Reflect/refract decision |
| ni (IOR)       | Material IOR               | Snell's law (refraction) |