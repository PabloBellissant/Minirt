/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:55:34 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/02 11:00:36 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "calc.h"

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

void	shade(t_buffers *buffers, int pixel, t_scene *scene, t_data *data)
{
	t_object	*lights;
	size_t		m;

	data->mlx->img.addr[buffers->hits[pixel].id] = rgb_ftoi(buffers->shadows_result[pixel].color_through).rgb;
	return;
	lights = scene->lights.data;
	scene->phong.v = vec3_normalize(vec3_sub(scene->camera.pos, buffers->hits[pixel].hit_point));
	m = 0;
	while (m < scene->lights.num_elements)
	{
		scene->phong.d[m] = lights[m].light.rgb;
		scene->phong.l[m] = buffers->shadows[pixel].ray.dir;
		scene->phong.r[m] = reflection(buffers->hits[pixel].normal, scene->phong.l[m]);
		m++;
	}
	const t_rgb	ambient = vec3_mult(buffers->hits[pixel].hit_rgb,
							  vec3_scale(scene->ambient.rgb, buffers->hits[pixel].hit_ambient));
	t_rgb		diffuse_m;
	t_rgb		specular_m;
	t_rgb		i_p;
	t_rgb		color_through;
	i_p = rgb(0, 0, 0);
	m = 0;
	while (m < scene->lights.num_elements)
	{
		color_through = buffers->shadows_result[pixel].color_through;
		data->scene.phong.d[m] = rgb_mult(data->scene.phong.d[m], color_through);
		diffuse_m = vec3_mult(get_diffuse(data->scene.phong.l[m], data->scene.phong.d[m],
				buffers->hits[pixel].normal, buffers->hits[pixel].hit_rgb), buffers->hits[pixel].hit_rgb);
		specular_m = get_specular(data->scene.phong.r[m], data->scene.phong.v, buffers->hits[pixel].ks, buffers->hits[pixel].ns);
		specular_m = rgb_mult(specular_m, vec3_mult(data->scene.phong.d[m], color_through));
		i_p = vec3_add(i_p, vec3_add(diffuse_m, specular_m));
		m++;
	}
	data->mlx->img.addr[buffers->hits[pixel].id] = rgb_ftoi(vec3_add(vec3_add(i_p, ambient), buffers->hits[pixel].ke)).rgb;
}
