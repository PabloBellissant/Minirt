/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:37:35 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 05:57:55 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "calc.h"
#include "vec3.h"

t_vec3		*phong_path(t_scene *scene, t_ray *ray, t_vec3 *i_p);
static void	fill_phong(t_ray *ray, t_scene *scene);

static void light_hit_register_data(t_ray *restrict ray, t_light *restrict light, float t_min)
{
    t_vec3 hit_dir;
    t_vec3 hit_point;
    
    // Calculate hit point
    hit_dir = ray->dir;
    vec3_scale(&hit_dir, t_min);
    vec3_add(&ray->pos, &hit_dir, &hit_point);
    
    // Normal points toward camera for hollow circle effect
    vec3_sub(&hit_point, &light->pos, &ray->hit_normal);
    vec3_normalize(&ray->hit_normal);
    
    ray->hit_rgb = light->rgb;
    ray->pos = hit_point;
}
#include <float.h>
#define OFFSET 0.001f

int light_intersect(t_ray *ray, t_light *light, float *t)
{
    t_vec3 oc;
    vec3_sub(&ray->pos, &light->pos, &oc);
    
    // Small sphere around light position for intersection
    float	radius = .1f; // Adjust for hit area size
    float	a;
    float	b;
    float	c;
    vec3_dot(&ray->dir, &ray->dir, &a);
    vec3_dot(&oc, &ray->dir, &b);
    b *= 2.0f;
    vec3_dot(&oc, &oc, &c);
    c = c - radius * radius;
    
    float discriminant = b * b - 4 * a * c;
    if (discriminant == 0)
        return (0);
    
    float t1 = (-b - sqrtf(discriminant)) / (2 * a);
    float t2 = (-b + sqrtf(discriminant)) / (2 * a);
    
    *t = (t1 > OFFSET) ? t1 : t2;
    return (*t > OFFSET);
}

float light_hit_register(t_ray *ray, t_scene *scene)
{
	t_vector*light_vec;
    t_light *lights;
    float   t_min = FLT_MAX;
    float   t_current;
    int     hit_light_idx = -1;
    int     i = 0;

	light_vec = &scene->lights;
    lights = light_vec->data;
    
    //printf("%f\n", lights[0].pos.x);
    while (i < (int)light_vec->num_elements)
    {
        if (light_intersect(ray, &lights[i], &t_current))
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
    light_hit_register_data(ray, &lights[hit_light_idx], t_min);
    return (t_min);
}

t_color render_light_hollow_circle(t_ray *ray)
{
    t_vec3	view_dir = ray->dir;
   	float	rim_factor;
   	vec3_dot(&view_dir, &ray->hit_normal, &rim_factor);
    rim_factor = 1.0f - fabs(rim_factor);
   
    // Only show orange color on the rim (hollow effect)
    if (rim_factor)
    {
        t_color orange;
        orange.r = (unsigned char)(255 * rim_factor);
        orange.g = (unsigned char)(127 * rim_factor);
        orange.b = 0;
        return orange;
    }
    
    return (t_color){.rgb = 0}; // Transparent center
}

t_color	ray_path(t_ray *ray, t_scene *scene)
{
	float	hit_distance;
	float	hit_distance_light;
	t_rgb	color_accumulator;
	t_color	final_color;
	t_ray	og;

	og = *ray;
	hit_distance = hit_register(ray, &scene->objects);
	hit_distance_light = light_hit_register(&og, scene);
	if ((hit_distance_light > 0) && ((hit_distance == 0) || (hit_distance_light < hit_distance)))
		final_color = render_light_hollow_circle(&og);
	if ((final_color.r <= 200) && (final_color.g <= 100))
	{
		if (hit_distance == 0)
			return ((t_color){.rgb = 0});
		fill_phong(ray, scene);
		color_accumulator = (t_rgb){{{0, 0, 0}}};
		phong_path(scene, ray, &color_accumulator);
		rgb_clamp(&color_accumulator, 0.0f, 1.0f);
		rgb_to_color(&color_accumulator, &final_color);
	}
	return (final_color);
}

/*
	Will return the reflection direction
	needs the normalized normal and normalized direction to light
*/
static t_vec3	*reflection(const t_vec3 *normal, const t_vec3 *light_dir,
					t_vec3 *out)
{
	float	r;
	t_vec3	temp;

	vec3_dot(light_dir, normal, &r);
	r *= 2;
	temp = *normal;
	vec3_scale(&temp, r);
	return (vec3_sub(&temp, light_dir, out));
}

static void	fill_phong(t_ray *ray, t_scene *scene)
{
	t_object	*lights;
	size_t		m;

	vec3_sub(&scene->camera.pos, &ray->pos, &scene->phong.v);
	vec3_normalize(&scene->phong.v);
	m = 0;
	lights = (t_object *)scene->lights.data;
	while (m < scene->lights.num_elements)
	{
		scene->phong.d[m] = lights[m].light.rgb;
		vec3_sub(&(lights[m].light.pos), &ray->pos, scene->phong.l + m);
		vec3_normalize(scene->phong.l + m);
		reflection(&ray->hit_normal, scene->phong.l + m, scene->phong.r + m);
		m++;
	}
}
