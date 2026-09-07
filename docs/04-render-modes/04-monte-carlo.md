# Monte Carlo Path Tracing (Index 3)

Monte Carlo path tracing samples the light transport using **importance-sampled GGX microfacets** with **chromatic dispersion** (wavelength-dependent refraction), producing physically accurate caustics, rainbows, and glossy reflections. Each ray scatters stochastically through the scene, accumulating energy across bounces until it exits to the skybox or hits an emissive surface.

## GGX Importance Sampling

The **GGX microfacet distribution** is used to importance-sample reflection and refraction directions. Instead of always reflecting in the specular direction, GGX samples a random microfacet normal **h** proportional to the roughness:

theta = arccos(sqrt((1 - u2) / (1 + (alpha^2 - 1) * u2))),  phi = 2*pi*u1

Where `alpha = roughness^2`, and `u1`, `u2` are uniform random numbers. The sampled half-vector **h** is used to compute the scattered direction for glossy reflection or refraction.

## Chromatic Dispersion

<table cellpadding="0" cellspacing="0" border="0" style="border:none;">
<tr><td><img src="../assets/img/diffraction.png" width="100%"></td><td><img src="../assets/img/diffraction2.png" width="100%"></td></tr>
</table>

*Chromatic dispersion in Monte Carlo mode: wavelength-dependent IOR produces physically accurate rainbow caustics and colored refractions.*

Dispersion models the **wavelength-dependent refractive index** of real materials. The ray's current `through_power` color is converted to a **spectral hue index** (0-360 degrees) via `rgb_to_spectrum_index()`. This hue is mapped to a wavelength factor in [-1, 1], and the effective IOR becomes:

eta_effective = eta_base + wavelength_factor * dispersion * (eta_base - 1)

This is implemented in `get_ni_by_color()`. When dispersion activates (first refraction on a diffracting path), the ray is assigned a **random RGB color** via `rainbow_color()`, which becomes the new `through_power` for subsequent bounces, multiplied by a **3x energy boost** to compensate for the splitting of white light into spectral components.

## Through-Power and Energy Boost

The initial `through_power` is `(0.33, 0.33, 0.33)` -- one-third per channel, matching the approximate energy distribution of visible light. After a diffracting event, the through-power is multiplied by a random rainbow color and 3x boost. The 3x factor compensates for the fact that only one random spectral component is followed rather than the full spectrum; on average, this preserves energy.

## Emissive Materials

When a ray hits an emissive surface (`ke > 0`), the path terminates immediately. The accumulation includes all previous bounces plus the emissive contribution, multiplied by the same 3x energy boost.

## Skybox

On **bounce 0** (primary ray miss), the skybox color is written directly to the pixel without scaling. On **bounce > 0** (secondary ray miss), the skybox color is multiplied by `accumulated_color x 3` and added, allowing the skybox to contribute color to bounces that exit the scene after internal reflections.

## Pipeline Diagram

```mermaid
flowchart TD
    START([Per-Pixel Kernel Start]) --> RAYGEN[Generate Primary Ray\ncalc_ray]

    RAYGEN --> BOUNCE_LOOP{while bounce < MAX_BOUNCE}

    BOUNCE_LOOP -->|bounce < 4| BVH_HIT[BVH Traversal\nhit_register_gpu]
    BOUNCE_LOOP -->|bounce >= 4| DONE([Done - pixel complete])

    BVH_HIT --> IS_MISS{Object hit?}

    IS_MISS -->|Miss| SKYBOX_CHECK{bounce == 0?}

    SKYBOX_CHECK -->|Yes| SKYBOX_DIRECT[img += skybox color]
    SKYBOX_CHECK -->|No| SKYBOX_ACCU[img += skybox x accu x 3]

    SKYBOX_DIRECT --> DONE
    SKYBOX_ACCU --> DONE

    IS_MISS -->|Hit| SAMPLE_MATS[Sample materials\nkd, ke, normal, roughness, metalness, opacity]

    SAMPLE_MATS --> IS_EMISSIVE{ke > 0?}

    IS_EMISSIVE -->|Yes| EMIT_ACCU[accu += ke x through_power\nimg += accu x ke x 3]
    EMIT_ACCU --> DONE

    IS_EMISSIVE -->|No| DECIDE_REFLECT{random < opacity?}

    DECIDE_REFLECT -->|Reflect| GGX_REFLECT[GGX sample reflection\nray.dir = reflect(ray.dir, sample_ggx_gpu(normal))]

    DECIDE_REFLECT -->|Refract| GGX_REFRACT[GGX sample from incident\nray.dir = sample_ggx_gpu(ray.dir)]

    GGX_REFRACT --> IS_DIFFRACT{is_diffract == 0?}

    IS_DIFFRACT -->|First diffract| SET_DISPERSION[Set is_diffract = 1\nthrough_power x= rainbow_color x 3]

    IS_DIFFRACT -->|Already diffracting| SKIP_DISPERSION[Keep through_power]

    SET_DISPERSION --> REFRACT_WITH_DISP[Refract with chromatic IOR\nget_ni_by_color]
    SKIP_DISPERSION --> REFRACT_WITH_DISP

    REFRACT_WITH_DISP --> BOUNCE_ACCUM[accu += kd x (1-reflectivity) x through_power\nthrough_power x= reflectivity]
    GGX_REFLECT --> BOUNCE_ACCUM

    BOUNCE_ACCUM --> ADVANCE_RAY[Advance ray origin\noffset by epsilon]

    ADVANCE_RAY --> BOUNCE_INC[bounce++]
    BOUNCE_INC --> BOUNCE_LOOP
```
