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
#include "minirt.h"
#include "vectors.h"

#define SHADOW_BIAS 0.001f // offset ?

/*
	k_a = object reflection ratio (t_rgb)
	k_d = object diffuse ratio (t_rgb)
	k_s = object specular ratio (t_rgb)
	alpha = object reflection coefficient (float)

	i_a = ambient light color (t_rgb)
	i_d(_m) = light color (t_rgb)
	i_s = specular
*/

const t_vec3	i_s = (t_vec3){{1.0f, 1.0f, 1.0f}};

static t_rgb	get_diffuse(const t_vec3 l_m, const t_rgb i_d, const t_vec3 n, const t_vec3 k_d)
{
	const float	surface_faces_light = vec3_dot(l_m, n);

	if (surface_faces_light <= 0)
		return (rgb(0, 0, 0));
	return (vec3_scale(vec3_mult(k_d, i_d), surface_faces_light));
}

static t_rgb	get_specular(const t_vec3 r_m, const t_vec3 v, t_vec3 k_s, const float n_s)
{
	float	surface_faces_camera;

	surface_faces_camera = vec3_dot(r_m, v);
	if (surface_faces_camera <= 0)
		return (rgb(0, 0, 0));
	surface_faces_camera = powf(surface_faces_camera, n_s);
	return (vec3_scale(k_s, surface_faces_camera));
}

t_rgb	hit_register_light(t_ray *ray, t_data *data, t_vec3 light_pos);

static t_rgb	get_color_through(t_data *data, t_vec3 hit_point,
		t_vec3 light_pos, t_vec3 normal)
{
	const t_vec3	offset_point = vec3_add(hit_point,
			vec3_scale(normal, SHADOW_BIAS));
	t_ray			ray;
	t_vec3			to_light;
	t_rgb			color_through;

	ray.pos = offset_point;
	to_light = vec3_sub(light_pos, offset_point);
	ray.dir = vec3_normalize(to_light);
	color_through = hit_register_light(&ray, data, light_pos);
	return (color_through);
}

/*
	Function that comptes the color of a pixel based on Phong's reflection model
	m is each light sources
*/
t_rgb	phong_path(t_data *data, t_ray *ray)
{
	const t_rgb	ambient = vec3_mult(ray->hit_rgb,
							  vec3_scale(data->scene.ambient.rgb, ray->hit_ambient));
	t_rgb		diffuse_m;
	t_rgb		specular_m;
	t_rgb		i_p;
	size_t		m;
	t_rgb		color_through;

	m = 0;
	i_p = rgb(0, 0, 0);
	while (m < data->scene.lights.num_elements)
	{
		color_through = get_color_through(data, ray->pos,
				(((t_object *)(data->scene.lights.data))[m].light.pos),
				ray->hit_normal);
		data->scene.phong.d[m] = rgb_mult(data->scene.phong.d[m], color_through);
		diffuse_m = vec3_mult(get_diffuse(data->scene.phong.l[m], data->scene.phong.d[m],
				ray->hit_normal, ray->hit_rgb), ray->hit_rgb);
		specular_m = get_specular(data->scene.phong.r[m], data->scene.phong.v, ray->hit_mat->ks, ray->hit_mat->ns);
		specular_m = rgb_mult(specular_m, vec3_mult(data->scene.phong.d[m], color_through));
		i_p = vec3_add(i_p, vec3_add(diffuse_m, specular_m));
		m++;
	}
	return (vec3_add(vec3_add(i_p, ambient), ray->hit_mat->ke));
}
