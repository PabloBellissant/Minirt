/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_materials.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 02:08:32 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/16 02:08:32 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "colors_types.h"
#include "minirt.h"
#include "rasterizer.h"
#include "render.h"
#include "rgb_special1.h"
#include "vec3_operations.h"
#include "vec3_scalar.h"
#include "vec3_special1.h"
#include "vec3_special2.h"
#include "vectors_types.h"
#include <errno.h>

float	sample_binary_texture(const t_texture *texture_list, int id, t_vec2 uv);
t_vec3	apply_normal_map(t_vec3 normal, t_vec3 nmap, t_vec3 tangent, t_vec3 bitangent);

t_rgb	sample_texture(const t_texture *texture_list, int id, t_vec2 uv)
{
	int			x;
	int			y;
	t_rgb_int	color;
	int			offset;

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

t_vec3	vec3_make(float value)
{
	return (vec3(value, value, value));
}

t_rgb	get_f0(float metalness, float ior, t_rgb ks)
{
	float	no_metal_f0;

	no_metal_f0 = ((ior - 1.0f) / (ior + 1.0f));
	no_metal_f0 *= no_metal_f0;
	return (rgb_lerp(vec3_make(no_metal_f0), ks, metalness));
}


t_vec3 vec3_refract(t_vec3 ray_dir, t_vec3 normal, float eta)
{
	float cosi = -vec3_dot(ray_dir, normal);
	float cost2 = 1.0f - eta * eta * (1.0f - cosi * cosi);
	if (cost2 < 0.0f)
		return (ray_dir);
	float cost = sqrtf(cost2);

	t_vec3 refr_dir = vec3_add(
		vec3_scale(ray_dir, eta),
		vec3_scale(normal, eta * cosi - cost)
	);
	return (vec3_normalize(refr_dir));
}

#define EPSILON 0.001f
float	get_sphere_t_out(t_ray *ray, t_object *o);

void	pass_through_sphere(t_vec3 *origin, t_vec3 *dir, t_hit *hit, float ni)
{
	float	t_out;
	t_ray	temp;

	*dir = vec3_refract(*dir, hit->normal, 1.0f / ni);
	temp.origin = hit->hit_point;
	temp.dir = *dir;
	*origin = temp.origin;
	t_out = get_sphere_t_out(&temp, hit->hit_obj);
	*origin = vec3_add(*origin, vec3_scale(*dir, t_out + EPSILON));
	*dir = vec3_refract(*dir, vec3_normalize(vec3_sub(hit->hit_obj->sphere.pos, *origin)), ni / 1.0f);
}

void	pass_through_plane(t_vec3 *origin, t_hit *hit)
{
	*origin = vec3_add(hit->hit_point, vec3_scale(hit->hit_obj->plane.normal, -EPSILON));
}

void	pass_through_triangle(t_vec3 *origin, t_vec3 *dir, t_hit *hit, float ni)
{
    float	cos_theta;
    
	cos_theta = vec3_dot(*dir, hit->normal);	
	if (cos_theta < 0.0f)
    	*dir = vec3_refract(*dir, hit->normal, 1.0f / ni);
	else
    	*dir = vec3_refract(*dir, vec3_neg(hit->normal), ni / 1.0f);
    *origin = vec3_add(hit->hit_point, vec3_scale(*dir, EPSILON));
}

void	pass_through(t_vec3 *origin, t_vec3 *dir, t_hit *hit, float ni)
{
	if (hit->hit_obj->type == SPHERE)
		pass_through_sphere(origin, dir, hit, ni);
	else if (hit->hit_obj->type == PLANE)
		pass_through_plane(origin, hit);
	else if (hit->hit_obj->type == TRIANGLE)
		pass_through_triangle(origin, dir, hit, ni);
}

t_vec3	vec3_inv(t_vec3 vec);

void	sample_materials(t_buffers *buffers, int pixel, t_texture *tex, t_mat *mat)
{
	t_vec3			tangent;
	t_vec3			bitangent;
	t_rgb			nmap;
	t_rgb			f0;
	float			roughness;
	t_ray			*ray;
	t_hit_mat_data	hit_data;
(void) hit_data;
	mat = mat + buffers->hits[pixel].mat_id;
	ray = &buffers->rays[buffers->hits[pixel].id];
	buffers->hits[pixel].hit_rgb = sample_texture(tex, mat->kd_id, buffers->hits[pixel].uv);
	buffers->hits[pixel].hit_ambient = sample_binary_texture(tex, mat->ambient_id, buffers->hits[pixel].uv);
	hit_data.hit_opacity = sample_binary_texture(tex, mat->opacity_id, buffers->hits[pixel].uv);
	nmap = sample_texture(tex, mat->normal_id, buffers->hits[pixel].uv);
	tangent = get_tangent(buffers->hits[pixel].normal);
	bitangent = get_bitangent(buffers->hits[pixel].normal, tangent);
	buffers->hits[pixel].normal = apply_normal_map(buffers->hits[pixel].normal, nmap, tangent, bitangent);
	buffers->hits[pixel].ks = mat->ks;
	buffers->hits[pixel].ke = mat->ke;
	buffers->hits[pixel].ns = mat->ns;
	f0 = get_f0(mat->pm, mat->ni, buffers->hits[pixel].ks);
	roughness = sample_binary_texture(tex, mat->roughness_id, buffers->hits[pixel].uv);
	buffers->hits[pixel].reflectivity = get_reflect(ray->dir, buffers->hits[pixel].normal, roughness, f0);
	buffers->hits[pixel].reflectivity = vec3_clamp(buffers->hits[pixel].reflectivity, 0.0f, 1.0f);
	if (ray->iteration > MAX_ITER || vec3_length(buffers->hits[pixel].reflectivity) < 0.05f)
		buffers->hits[pixel].hit = false;
	else
	{
		ray->refract.through_power[ray->refract.count] = vec3_scale(ray->through_power, 1.0f - hit_data.hit_opacity);
		if (vec3_length(ray->refract.through_power[ray->refract.count]) > 0.05)
		{
			ray->refract.dir[ray->refract.count] = ray->dir;
			ray->refract.origin[ray->refract.count] = ray->origin;
			ray->through_power = vec3_sub(ray->through_power, ray->refract.through_power[ray->refract.count]);
			pass_through(&ray->refract.origin[ray->refract.count], &ray->refract.dir[ray->refract.count], &buffers->hits[pixel], mat->ni);
			++ray->refract.count;
		}
		ray->origin = buffers->hits[pixel].hit_point;
		ray->dir = vec3_reflect(ray->dir, buffers->hits[pixel].normal);
		ray->inv_dir = vec3_inv(ray->dir);
		ray->iteration++;
	}
}
