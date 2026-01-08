/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 00:04:48 by pabellis          #+#    #+#             */
/*   Updated: 2026/01/02 00:04:48 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_wrapper.h"
#include "calc.h"

t_vec3	vec3_reflect(t_vec3 ray, t_vec3 normal)
{
	t_vec3	scaled_normal;

	scaled_normal = vec3_scale(normal, 2 * vec3_dot(ray, normal));
	return (vec3_sub(ray, scaled_normal));
}

t_vec3	get_reflect(t_vec3 ray_dir, t_vec3 normal, float roughness, t_vec3 F0)
{
	t_vec3	fresnel;
	float	cos_theta;
	float	glossy_factor;
	t_vec3	specular;

	cos_theta = fabsf(vec3_dot(ray_dir, normal));
	fresnel = vec3_scale(vec3_sub(vec3(1, 1, 1), F0),
			powf(1.0f - cos_theta, 5.0f));
	fresnel = vec3_add(F0, fresnel);
	glossy_factor = 1.0f - (roughness * roughness);
	specular = vec3_scale(fresnel, glossy_factor);
	return (specular);
}

t_rgb	get_f0(float metalness, float ior, t_rgb ks)
{
	float	no_metal;

	no_metal = ((ior - 1.0f) / (ior + 1.0f));
	no_metal *= no_metal;
	return (rgb_lerp(vec3(no_metal, no_metal, no_metal), ks, metalness));
}

t_vec3	fresnel_schlick(float cos_theta, t_vec3 f0)
{
	t_vec3	one_minus_f0;
	float	factor;

	factor = powf(1.0f - cos_theta, 5.0f);
	one_minus_f0 = vec3(1.0f - f0.x, 1.0f - f0.y, 1.0f - f0.z);
	one_minus_f0 = vec3_scale(one_minus_f0, factor);
	return (vec3_add(f0, one_minus_f0));
}

t_rgb	get_reflectivity(
	t_mat *mat, t_hit *hit, t_texture *tex, t_ray *ray)
{
	t_rgb	f0;
	t_rgb	reflectivity;

	f0 = get_f0(sample_gray_level_texture(tex, mat->metalness_id, hit->uv),
			mat->ni, mat->ks);
	reflectivity = fresnel_schlick(fabsf(vec3_dot(ray->dir, hit->normal)), f0);
	reflectivity = rgb_clamp(reflectivity, 0.0f, 1.0f);
	return (reflectivity);
}
