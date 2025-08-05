/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:37:35 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 05:12:55 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "calc.h"
#include "vec3.h"

t_vec3		*phong_path(t_scene *scene, t_ray *ray, t_vec3 *i_p);
static void	fill_phong(t_ray *ray, t_scene *scene);

t_color	ray_path(t_ray *ray, t_scene *scene)
{
	float	hit_result;
	t_rgb	color_accumulator;
	t_color	final_color;

	hit_result = hit_register(ray, &scene->objects);
	if (hit_result == 0)
		return ((t_color){.rgb = 0});
	fill_phong(ray, scene);
	color_accumulator = (t_rgb){{{0, 0, 0}}};
	phong_path(scene, ray, &color_accumulator);
	rgb_clamp(&color_accumulator, 0.0f, 1.0f);
	rgb_to_color(&color_accumulator, &final_color);
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
