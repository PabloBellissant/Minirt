/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_sample_materials.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 02:08:32 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/28 16:42:00 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "minirt.h"
#include "render.h"
#include "calc.h"

t_vec3	vec3_reflect(t_vec3 ray, t_vec3 normal);
t_vec3	get_reflect(t_vec3 ray_dir, t_vec3 normal, float roughness, t_vec3 F0);
t_vec3	vec3_inv(t_vec3 vec);
void	refract(t_vec3 *origin, t_vec3 *dir, t_hit *hit, float ni);

t_vec3	vec3_rand(void);
t_vec3	vec3_negate(t_vec3 v);
float	rand_f(void);

t_vec3	fresnel_schlick(float cos_theta, t_vec3 f0);

t_vec3	sample_ggx(t_vec3 normal, float roughness)
{
	t_vec3	tangent;
	float	phi;
	float	cos_theta;
	float	sin_theta;
	t_vec3	h;

	if (roughness <= 0.01)
		return (normal);
	phi = rand_f();
	cos_theta = sqrtf(
			(1.0f - phi) / (1.0f + (powf(roughness, 4.0f) - 1.0f) * phi));
	sin_theta = sqrtf(1.0f - cos_theta * cos_theta);
	phi = 2.0f * M_PI * rand_f();
	h.x = cosf(phi) * sin_theta;
	h.y = sinf(phi) * sin_theta;
	h.z = cos_theta;
	tangent = get_tangent(normal);
	return (vec3_normalize(
			vec3_add(
				vec3_add(vec3_scale(tangent, h.x),
					vec3_scale(get_bitangent(normal, tangent), h.y)),
				vec3_scale(normal, h.z)
			)
		));
}

void	apply_hit_data(
	t_hit *hit, t_mat *mat, t_texture *tex, t_hit_mat_data *data)
{
	t_rgb	normal_map;
	t_vec3	tangent;
	t_vec3	bitangent;

	hit->hit_rgb = sample_texture(tex, mat->kd_id, hit->uv);
	hit->hit_ambient = sample_gray_level_texture(
			tex, mat->ambient_id, hit->uv);
	data->hit_opacity = sample_gray_level_texture(
			tex, mat->opacity_id, hit->uv);
	normal_map = sample_texture(tex, mat->normal_id, hit->uv);
	tangent = get_tangent(hit->normal);
	bitangent = get_bitangent(hit->normal, tangent);
	hit->normal = apply_normal_map(
			hit->normal, normal_map, tangent, bitangent);
	hit->ke = mat->ke;
	data->roughness = sample_gray_level_texture(
			tex, mat->roughness_id, hit->uv);
	data->metalness = sample_gray_level_texture(
			tex, mat->metalness_id, hit->uv);
}

t_rgb	get_reflectivity(
			t_mat *mat, t_hit *hit, t_texture *tex, t_ray *ray);

static void	gen_next_ray(
	t_ray *ray, t_texture *tex, t_hit_mat_data *data, t_hit *hit)
{
	ray->origin = hit->hit_point;
	hit->reflectivity = get_reflectivity(data->mat, hit, tex, ray);
	data->hit_opacity = fmaxf(
			data->hit_opacity, hit->reflectivity.r);
	if (rand_f() > data->hit_opacity)
	{
		refract(&ray->origin, &ray->dir, hit, data->mat->ni);
		ray->dir = sample_ggx(ray->dir, data->roughness);
		hit->reflectivity = vec3_sub_scalar(
				vec3(1, 1, 1), data->hit_opacity);
	}
	else
		ray->dir = vec3_reflect(ray->dir, sample_ggx(
					hit->normal, data->roughness));
	ray->inv_dir = vec3_inv(ray->dir);
	ray->iteration++;
}

void	path_sample_materials(
	t_buffers *buffers, int pixel, t_texture *tex, t_mat *mat)
{
	t_ray			*ray;
	t_hit_mat_data	hit_data;

	hit_data.mat = mat + buffers->hits[pixel].mat_id;
	ray = &buffers->rays[buffers->hits[pixel].id];
	apply_hit_data(&buffers->hits[pixel], hit_data.mat, tex, &hit_data);
	if (ray->iteration > 1)
	{
		buffers->hits[pixel].hit = false;
		return ;
	}
	gen_next_ray(ray, tex, &hit_data, &buffers->hits[pixel]);
}

void	path_sample_materials_loop(
	t_buffers *buffers, t_texture *tex, t_mat *mat, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		path_sample_materials(buffers, i, tex, mat);
		++i;
	}
}
