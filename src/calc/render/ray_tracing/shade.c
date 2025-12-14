/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:55:34 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/14 03:19:34 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_types.h"
#include "minirt.h"
#include "calc.h"
#include "mlx_draw.h"
#include "rgb_operations.h"
#include "vec3_operations.h"

static t_vec3	reflection(const t_vec3 normal, const t_vec3 light_dir)
{
	const float	r = vec3_dot(light_dir, normal) * 2;

	return (vec3_sub(vec3_scale(normal, r), light_dir));
}

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


t_rgb	get_color_through(t_data *data, t_vec3 hit_point,
		t_vec3 light_pos, t_vec3 normal)
{
	const t_vec3	offset_point = vec3_add(hit_point,
			vec3_scale(normal, 0.001f));
	t_ray			ray;
	t_vec3			to_light;
	t_rgb			color_through;

	ray.origin = offset_point;
	to_light = vec3_sub(light_pos, offset_point);
	ray.dir = vec3_normalize(to_light);
	(void) data;
	color_through = rgb(1,1,1);//hit_register_light(&ray, data, light_pos);
	return (color_through);
}

t_vec3 vec3_make(float val);

void	shade(t_buffers *buffers, int pixel, t_scene *scene, t_data *data)
{
	t_object	*lights;
	size_t		m;

	lights = scene->lights.data;
	scene->phong.v = vec3_normalize(vec3_sub(scene->camera.pos, buffers->hits[pixel].hit_point));
	m = 0;
	while (m < scene->lights.num_elements)
	{
		scene->phong.l[m] = vec3_normalize(vec3_sub(lights[m].light.pos,
					buffers->hits[pixel].hit_point));
		scene->phong.r[m] = reflection(buffers->hits[pixel].normal, scene->phong.l[m]);
		m++;
	}
	const t_rgb	ambient = vec3_mult(buffers->hits[pixel].hit_rgb,
							  vec3_scale(scene->ambient.rgb, buffers->hits[pixel].hit_ambient));
	t_rgb		diffuse_m;
	t_rgb		specular_m;
	t_rgb		i_p;
	t_rgb		color_through;
	t_rgb		phong_d;
	i_p = rgb(0, 0, 0);
	m = 0;
	while (m < scene->lights.num_elements)
	{
			color_through = get_color_through(data, buffers->hits[pixel].hit_point, lights[m].light.pos, buffers->hits[pixel].normal);
		phong_d = rgb_mult(lights[m].light.rgb, color_through);
		diffuse_m = vec3_mult(get_diffuse(data->scene.phong.l[m], phong_d,
				buffers->hits[pixel].normal, buffers->hits[pixel].hit_rgb), buffers->hits[pixel].hit_rgb);
		specular_m = get_specular(data->scene.phong.r[m], data->scene.phong.v, buffers->hits[pixel].ks, buffers->hits[pixel].ns);
		specular_m = rgb_mult(specular_m, vec3_mult(phong_d, color_through));
		i_p = vec3_add(i_p, vec3_add(diffuse_m, specular_m));
		m++;
	}
	t_rgb	color = vec3_add(vec3_add(i_p, ambient), buffers->hits[pixel].ke);
	color = rgb_mult(color, buffers->rays[buffers->hits[pixel].id].through_power);
	color = rgb_mult(color, vec3_sub(vec3(1, 1, 1), buffers->hits[pixel].reflectivity));
	buffers->rays[buffers->hits[pixel].id].accumulated_color = rgb_add(buffers->rays[buffers->hits[pixel].id].accumulated_color, color);
	buffers->rays[buffers->hits[pixel].id].through_power = vec3_mult(buffers->rays[buffers->hits[pixel].id].through_power, buffers->hits[pixel].reflectivity);
}
