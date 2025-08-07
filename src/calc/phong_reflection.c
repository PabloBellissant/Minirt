/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_reflection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:49:47 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/07 09:40:46 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "calc.h"
#include "vectors.h"

#define SHADOW_BIAS 0.001f

/*
	k_a = object reflection ratio (t_rgb)
	k_d = object diffuse ratio (t_rgb)
	k_s = object specular ratio (t_rgb)
	alpha = object reflection coefficient (float)

	i_a = ambient light color (t_rgb)
	i_d(_m) = light color (t_rgb)
	i_s = specular
*/
const t_vec3	k_d = (t_vec3){{0.752f, 0.606f, 0.226f}};
const t_vec3	k_s = (t_vec3){{0.628f, 0.556f, 0.366f}};
const t_vec3	i_s = (t_vec3){{1.0f, 1.0f, 1.0f}};
const float		alpha = 55.2f;

static t_rgb	get_diffuse(const t_vec3 l_m, const t_rgb i_d, const t_vec3 n)
{
	const float	surface_faces_light = vec3_dot(l_m, n);

	if (surface_faces_light <= 0)
		return (rgb(0, 0, 0));
	return (vec3_scale(vec3_mult(k_d, i_d), surface_faces_light));
}

static t_rgb	get_specular(const t_vec3 r_m, const t_vec3 v)
{
	float	surface_faces_camera;

	surface_faces_camera = vec3_dot(r_m, v);
	if (surface_faces_camera <= 0)
		return (rgb(0, 0, 0));
	surface_faces_camera = powf(surface_faces_camera, alpha);
	return (vec3_scale(vec3_mult(k_s, i_s), surface_faces_camera));
}

static int	is_light_blocked(t_scene *scene, t_vec3 hit_point,
		t_vec3 light_pos, t_vec3 normal)
{
	const t_vec3	offset_point = vec3_add(hit_point,
			vec3_scale(normal, SHADOW_BIAS));
	t_ray			shadow_ray;
	t_vec3			to_light;
	float			light_distance;
	float			hit_distance;

	shadow_ray.pos = offset_point;
	to_light = vec3_sub(light_pos, offset_point);
	light_distance = vec3_length(to_light);
	shadow_ray.dir = vec3_normalize(to_light);
	hit_distance = hit_register(&shadow_ray, &scene->objects);
	return ((hit_distance > 0) && (hit_distance < light_distance));
}

/*
	Function that comptes the color of a pixel based on Phong's reflection model
	m is each light sources
*/
t_rgb	phong_path(t_scene *scene, t_ray *ray)
{
	const t_rgb	ambient = vec3_mult(ray->hit_rgb, scene->ambient.rgb);
	t_rgb		diffuse_m;
	t_rgb		specular_m;
	t_rgb		i_p;
	size_t		m;

	m = 0;
	i_p = rgb(0, 0, 0);
	while (m < scene->lights.num_elements)
	{
		if (is_light_blocked(scene, ray->pos,
				(((t_object *)(scene->lights.data))[m].light.pos),
				ray->hit_normal))
		{
			m++;
			continue ;
		}
		diffuse_m = get_diffuse(scene->phong.l[m], scene->phong.d[m],
				ray->hit_normal);
		specular_m = get_specular(scene->phong.r[m], scene->phong.v);
		i_p = vec3_add(i_p, vec3_add(diffuse_m, specular_m));
		m++;
	}
	return (vec3_add(i_p, ambient));
}
