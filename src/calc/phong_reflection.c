/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_reflection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 01:49:47 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/05 05:13:04 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "calc.h"
#include "vec3.h"

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
const t_vec3	k_d = (t_vec3){{{0.752f, 0.606f, 0.226f}}};
const t_vec3	k_s = (t_vec3){{{0.628f, 0.556f, 0.366f}}};
const t_vec3	i_s = (t_vec3){{{1.0f, 1.0f, 1.0f}}};
const float		alpha = 55.2f;

static t_rgb	*get_ambient(const t_rgb *k_a, const t_rgb *i_a, t_rgb *out)
{
	return (vec3_mult(k_a, i_a, out));
}

static t_rgb	*get_diffuse(const t_vec3 *l_m, const t_rgb *i_d,
	const t_vec3 *n, t_rgb *out)
{
	float	surface_faces_light;

	vec3_dot(l_m, n, &surface_faces_light);
	if (surface_faces_light <= 0)
	{
		*out = (t_rgb){{{0, 0, 0}}};
		return (out);
	}
	vec3_mult(&k_d, i_d, out);
	return (vec3_scale(out, surface_faces_light));
}

static t_rgb	*get_specular(const t_vec3 *r_m, const t_vec3 *v, t_rgb *out)
{
	float	surface_faces_camera;

	vec3_dot(r_m, v, &surface_faces_camera);
	if (surface_faces_camera <= 0)
	{
		*out = (t_rgb){{{0, 0, 0}}};
		return (out);
	}
	vec3_mult(&k_s, &i_s, out);
	surface_faces_camera = powf(surface_faces_camera, alpha);
	return (vec3_scale(out, surface_faces_camera));
}

static int	is_light_blocked(t_scene *scene, t_vec3 *hit_point,
		t_vec3 *light_pos, t_vec3 *normal)
{
	t_ray	shadow_ray;
	t_vec3	to_light;
	t_vec3	offset_point;
	float	light_distance;
	float	hit_distance;

	offset_point = *normal;
	vec3_scale(&offset_point, SHADOW_BIAS);
	vec3_add(hit_point, &offset_point, &offset_point);
	shadow_ray.pos = offset_point;
	vec3_sub(light_pos, &offset_point, &to_light);
	light_distance = vec3_length(&to_light);
	vec3_normalize(&to_light);
	shadow_ray.dir = to_light;
	hit_distance = hit_register(&shadow_ray, &scene->objects);
	return ((hit_distance > 0) && (hit_distance < light_distance));
}

/*
	Function that comptes the color of a pixel based on Phong's reflection model
	m is each light sources
*/
t_rgb	*phong_path(t_scene *scene, t_ray *ray, t_rgb *i_p)
{
	t_rgb	ambient;
	t_rgb	diffuse_m;
	t_rgb	specular_m;
	t_rgb	temp;
	size_t	m;

	get_ambient(&ray->hit_rgb, &(scene->ambient.rgb), &ambient);
	m = 0;
	while (m < scene->lights.num_elements)
	{
		if (is_light_blocked(scene, &ray->pos,
				&(((t_object *)(scene->lights.data))[m].light.pos),
				&ray->hit_normal))
		{
			m++;
			continue ;
		}
		get_diffuse(scene->phong.l + m, scene->phong.d + m,
			&ray->hit_normal, &diffuse_m);
		get_specular(scene->phong.r + m, &(scene->phong.v), &specular_m);
		vec3_add(&diffuse_m, &specular_m, &temp);
		vec3_add(i_p, &temp, i_p);
		m++;
	}
	return (vec3_add(i_p, &ambient, i_p));
}
