/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_materials.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 08:17:01 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/11 06:38:20 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vec3_operations.h"
#include "vec3_special2.h"

float	sample_binary_texture(const t_texture *texture_list, int id, t_vec2 uv);
t_vec3	apply_normal_map(t_vec3 normal, t_vec3 nmap, t_vec3 tangent, t_vec3 bitangent);


t_rgb	sample_texture(const t_texture *texture_list, int id, t_vec2 uv)
{
	int			x;
	int			y;
	t_rgb_int	color;
	int			offset;

	uv.u = uv.u - floorf(uv.u);
	uv.v = uv.v - floorf(uv.v);
	uv.v = 1.0f - uv.v;
	x = (int)(uv.u * (float)(texture_list[id].width));
	y = (int)(uv.v * (float)(texture_list[id].height));
	offset = y * texture_list[id].line_len + x * 3;
	color.r = texture_list[id].pixel[offset];
	color.g = texture_list[id].pixel[offset + 1];
	color.b = texture_list[id].pixel[offset + 2];
	return (rgb_itof(color));
}

float	sample_binary_texture(const t_texture *texture_list, int id, t_vec2 uv)
{
	int				x;
	int				y;
	int				offset;
	unsigned char	pixel;

	uv.u = uv.u - floorf(uv.u);
	uv.v = uv.v - floorf(uv.v);
	uv.v = 1.0f - uv.v;
	x = (int)(uv.u * (float)(texture_list[id].width));
	y = (int)(uv.v * (float)(texture_list[id].height));
	offset = y * texture_list[id].line_len + x;
	pixel = texture_list[id].pixel[offset];
	return ((float)pixel / 255.0f);
}

t_vec3	apply_normal_map(t_vec3 normal, t_vec3 nmap, t_vec3 tangent, t_vec3 bitangent)
{
    t_vec3	world_normal;
	t_vec3	n;

	n = vec3_sub_scalar(vec3_scale(nmap, 2.0f), 1);
	world_normal = vec3_add(vec3_add(
		vec3_scale(tangent, n.x),
		vec3_scale(bitangent, -n.y)),
		vec3_scale(normal, n.z));
    return (vec3_normalize(world_normal));
}

t_vec3	vec3_reflect(t_vec3 ray, t_vec3 normal)
{
	t_vec3 scaled_normal = vec3_scale(normal, 2 * vec3_dot(ray, normal));
	return (vec3_sub(ray, scaled_normal));
}


t_vec3 get_reflect(t_vec3 ray_dir, t_vec3 normal, float roughness, t_vec3 F0)
{
	t_vec3	fresnel;
	float	cos_theta;
	float	glossy_factor;
	t_vec3	specular;

	cos_theta = fabsf(vec3_dot(ray_dir, normal));
	fresnel = vec3_scale(vec3_sub(vec3(1, 1, 1), F0), powf(1.0f - cos_theta, 5.0f));
	fresnel = vec3_add(F0, fresnel);
	glossy_factor = 1.0f - (roughness * roughness);
	specular = vec3_scale(fresnel, glossy_factor);
	return (specular);
}

t_vec3	vec3_neg(t_vec3 v)
{
	t_vec3	res;

	res.x = -v.x;
	res.y = -v.y;
	res.z = -v.z;
	return (res);
}


void	sample_materials(t_buffers *buffers, int pixel, t_texture *tex, t_mat *mat)
{
	t_vec3	tangent;
	t_vec3	bitangent;
	t_rgb	nmap;

	mat = mat + buffers->hits[pixel].mat_id;
	buffers->hits[pixel].hit_rgb = sample_texture(tex, mat->kd_id, buffers->hits[pixel].uv);
	buffers->hits[pixel].hit_roughness = sample_binary_texture(tex, mat->roughness_id, buffers->hits[pixel].uv);
	buffers->hits[pixel].hit_ambient = sample_binary_texture(tex, mat->ambient_id, buffers->hits[pixel].uv);
	buffers->hits[pixel].hit_opacity = sample_binary_texture(tex, mat->opacity_id, buffers->hits[pixel].uv);
	nmap = sample_texture(tex, mat->normal_id, buffers->hits[pixel].uv);
	tangent = get_tangent(buffers->hits[pixel].normal);
	bitangent = get_bitangent(buffers->hits[pixel].normal, tangent);
	buffers->hits[pixel].normal = apply_normal_map(buffers->hits[pixel].normal, nmap, tangent, bitangent);
	buffers->hits[pixel].ks = mat->ks;
	buffers->hits[pixel].ke = mat->ke;
	buffers->hits[pixel].ns = mat->ns;
	buffers->hits[pixel].reflectivity = get_reflect(buffers->rays[buffers->hits[pixel].id].dir, buffers->hits[pixel].normal, buffers->hits[pixel].hit_roughness, vec3(0.1,0.1,0.1));
	buffers->hits[pixel].reflectivity = vec3_clamp(buffers->hits[pixel].reflectivity, 0.0f, 1.0f);
	buffers->rays[buffers->hits[pixel].id].origin = buffers->hits[pixel].hit_point;
	buffers->rays[buffers->hits[pixel].id].through_power = vec3_mult(buffers->rays[buffers->hits[pixel].id].through_power, buffers->hits[pixel].reflectivity);
	buffers->rays[buffers->hits[pixel].id].dir = vec3_reflect(buffers->rays[buffers->hits[pixel].id].dir, buffers->hits[pixel].normal);
}
