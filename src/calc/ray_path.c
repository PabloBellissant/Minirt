/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:37:35 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/07 00:43:01 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "calc.h"
#include "vectors.h"

t_vec3		phong_path(t_scene *scene, t_ray *ray);
static void	fill_phong(t_ray *ray, t_scene *scene);

static void light_hit_register_data(t_ray *restrict ray, t_light *restrict light, float t_min)
{
    t_vec3 hit_dir;
    t_vec3 hit_point;

    hit_dir = vec3_scale(ray->dir, t_min);
    hit_point = vec3_add(ray->pos, hit_dir);

    // Normal points toward camera for hollow circle effect
    ray->hit_normal = vec3_normalize(vec3_sub(hit_point, light->pos));
    
    ray->hit_rgb = light->rgb;
    ray->pos = hit_point;
}
#include <float.h>
#define OFFSET 0.001f

int light_intersect(t_ray *ray, t_light *light, float *t)
{
	const t_vec3	oc = vec3_sub(ray->pos, light->pos);

	// Small sphere around light position for intersection
	const float		radius = .1f; // Adjust for hit area size
	const float		a = vec3_dot(ray->dir, ray->dir);
	const float		b = vec3_dot(oc, ray->dir) * 2;
	const float		c = vec3_dot(oc, oc) - radius * radius;
	const float		discriminant = b * b - 4 * a * c;

	if (discriminant == 0)
		return (0);

	const float t1 = (-b - sqrtf(discriminant)) / (2 * a);
	const float t2 = (-b + sqrtf(discriminant)) / (2 * a);

	*t = (t1 > OFFSET) ? t1 : t2;
	return (*t > OFFSET);
}

float light_hit_register(t_ray *ray, t_scene *scene)
{
	t_object	*lights;
    float   t_min = FLT_MAX;
    float   t_current;
    int     hit_light_idx = -1;
    int     i = 0;

    lights = (t_object *)scene->lights.data;
    while (i < scene->lights.num_elements)
    {
        if (light_intersect(ray, &(lights[i].light), &t_current))
        {
            if (t_current < t_min)
            {
                t_min = t_current;
                hit_light_idx = i;
            }
        }
        ++i;
    }
    
    if (hit_light_idx == -1)
        return (0);
    
    // Register the light hit
    light_hit_register_data(ray, &(lights[hit_light_idx].light), t_min);
    return (t_min);
}

t_rgb_int render_light_hollow_circle(t_ray *ray)
{
   	const float	rim_factor = 1.0f - fabs(vec3_dot(ray->dir, ray->hit_normal));

    // Only show orange color on the rim (hollow effect)
    if (rim_factor)
        return (rgb_int(255 * rim_factor, 127 * rim_factor, 0));
    return (rgb_int(0, 0, 0));
}

t_rgb_int	ray_path(t_ray *ray, t_scene *scene)
{
	float	hit_distance;
	float	hit_distance_light;
	t_rgb_int	final_color = rgb_int(0, 0, 0);
	t_ray	og;

	og = *ray;
	hit_distance = hit_register(ray, &scene->objects);
	hit_distance_light = light_hit_register(&og, scene);
	if ((hit_distance_light > 0) && ((hit_distance == 0) || (hit_distance_light < hit_distance)))
		final_color = render_light_hollow_circle(&og);
	if ((final_color.r <= 200) && (final_color.g <= 100))
	{
		if (hit_distance == 0)
			return (rgb_int(0, 0, 0));
		fill_phong(ray, scene);
		final_color = rgb_ftoi(phong_path(scene, ray));
	}
	return (final_color);
}

/*
	Will return the reflection direction
	needs the normalized normal and normalized direction to light
*/
static t_vec3	reflection(const t_vec3 normal, const t_vec3 light_dir)
{
	const float	r = vec3_dot(light_dir, normal) * 2;

	return (vec3_sub(vec3_scale(normal, r), light_dir));
}

static void	fill_phong(t_ray *ray, t_scene *scene)
{
	t_object	*lights;
	size_t		m;

	scene->phong.v = vec3_normalize(vec3_sub(scene->camera.pos, ray->pos));
	m = 0;
	lights = (t_object *)scene->lights.data;
	while (m < scene->lights.num_elements)
	{
		scene->phong.d[m] = lights[m].light.rgb;
		scene->phong.l[m] = vec3_normalize(vec3_sub(lights[m].light.pos, ray->pos));
		scene->phong.r[m] = reflection(ray->hit_normal, scene->phong.l[m]);
		m++;
	}
}
