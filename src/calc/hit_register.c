/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_register.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 00:47:55 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/10 01:07:03 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>

#include "vectors.h"
#include "calc.h"
#include "minirt.h"

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

void	sample_mat(t_ray *ray, t_vec2 uv, t_data *data, int mat_id)
{
	t_rgb			nmap;
	t_vec3			new_normal;
	const t_texture	*tex = data->scene.texture.data;
	const t_mat		*mat = data->scene.mat.data;

	ray->hit_rgb = sample_texture(tex, mat[mat_id].kd_id, uv);
	ray->hit_roughness = sample_binary_texture(tex, mat[mat_id].roughness_id, uv);
	ray->hit_ambient = sample_binary_texture(tex, mat[mat_id].ambient_id, uv);
	ray->hit_opacity = sample_binary_texture(tex, mat[mat_id].opacity_id, uv);
	nmap = sample_texture(tex, mat[mat_id].normal_id, uv);
	new_normal = apply_normal_map(ray->hit_normal, nmap, ray->hit_tangent, ray->hit_bitangent);
	ray->hit_normal = new_normal;
}

void	apply_mat(t_ray *restrict ray, t_object *restrict o, t_params *params, t_data *data)
{
	t_vec3	hit_point;
	t_vec2	uv;

	hit_point = vec3_scale(ray->dir, o->t);
	hit_point = vec3_add(ray->origin, hit_point);
	if (o->type == TRIANGLE)
	{
		t_vec3	n0, n1, n2;

		t_vec3 v0v1 = o->triangle.edge_p1p0;
		t_vec3 v0v2 = o->triangle.edge_p2p0;
		t_vec3 v0p = vec3_sub(hit_point, o->triangle.p0.pos);
		float d00 = vec3_dot(v0v1, v0v1);
		float d01 = vec3_dot(v0v1, v0v2);
		float d11 = vec3_dot(v0v2, v0v2);
		float d20 = vec3_dot(v0p, v0v1);
		float d21 = vec3_dot(v0p, v0v2);

		float denom = d00 * d11 - d01 * d01;
		float bary_v = (d11 * d20 - d01 * d21) / denom;
		float bary_w = (d00 * d21 - d01 * d20) / denom;
		float bary_u = 1.0f - bary_v - bary_w;

		uv.x = bary_u * o->triangle.p0.uv.x +
					  bary_v * o->triangle.p1.uv.x +
					  bary_w * o->triangle.p2.uv.x;

		uv.y = bary_u * o->triangle.p0.uv.y +
					  bary_v * o->triangle.p1.uv.y +
					  bary_w * o->triangle.p2.uv.y;
		if (params->smooth_shading)
		{
			n0 = vec3_scale(o->triangle.p0.norm, bary_u);
			n1 = vec3_scale(o->triangle.p1.norm, bary_v);
			n2 = vec3_scale(o->triangle.p2.norm, bary_w);
			ray->hit_normal = vec3_add(n0, vec3_add(n1, n2));
		}
		else
			ray->hit_normal = vec3_add(o->triangle.p0.norm, vec3_add(o->triangle.p1.norm, o->triangle.p2.norm));
		ray->hit_normal = vec3_normalize(ray->hit_normal);
		ray->hit_tangent = get_tangent(ray->hit_normal);
		ray->hit_bitangent = get_bitangent(ray->hit_normal, ray->hit_tangent);
		sample_mat(ray, uv, data, o->mat_id);
	}
	else if (o->type == SPHERE)
	{
		ray->hit_normal = vec3_sub(hit_point, o->sphere.pos);
		ray->hit_normal = vec3_normalize(ray->hit_normal);
		uv.x = 0.5f + atan2f(ray->hit_normal.z, ray->hit_normal.x) / (2.0f * M_PIf);
		uv.y = 0.5f + asinf(ray->hit_normal.y) / M_PIf;

		ray->hit_tangent = get_tangent(ray->hit_normal);
		ray->hit_bitangent = get_bitangent(ray->hit_normal, ray->hit_tangent);
		sample_mat(ray, uv, data, o->mat_id);
	}
	else if (o->type == PLANE)
	{
		ray->hit_normal = o->plane.normal;
		ray->hit_tangent = o->plane.tangent;
		ray->hit_bitangent = o->plane.bitangent;

		t_vec3 local_point = vec3_sub(hit_point, o->plane.pos);
		uv.x = vec3_dot(local_point, ray->hit_tangent) * 0.1f;
		uv.y = vec3_dot(local_point, ray->hit_bitangent) * 0.1f;
		hit_point = vec3_add(hit_point, vec3_scale(ray->hit_normal, EPSILON));
		sample_mat(ray, uv, data, o->mat_id);
	}
	else if (o->type == CYLINDER)
	{
		t_vec3	axis;
		t_vec3	to_hit;
		axis = o->cylinder.rot;
		to_hit = vec3_sub(hit_point, o->cylinder.pos);
		axis = vec3_scale(axis, vec3_dot(to_hit, axis));
		axis = vec3_add(o->cylinder.pos, axis);
		ray->hit_normal = vec3_sub(hit_point, axis);
		ray->hit_normal = vec3_normalize(ray->hit_normal);
		ray->hit_rgb = o->cylinder.rgb;
		ray->hit_tangent = get_tangent(ray->hit_normal);
		ray->hit_bitangent = get_bitangent(ray->hit_normal, ray->hit_tangent);
	}
	ray->origin = hit_point;
}

t_object	*hit_sphere_bvh(t_ray *ray, t_sphere_bvh *bvh);

t_object	*hit_register(t_ray *ray, t_scene *scene)
{
	t_object	*bvh_ret;
	t_object	*plane_hit;

	if (scene->bvh.bvh_mode == 0)
		bvh_ret = hit_sphere_bvh(ray, scene->bvh.sphere_bvh);
	else
		bvh_ret = hit_aabb_bvh(ray, scene->bvh.aabb_bvh);
	if (bvh_ret)
	{
		plane_hit = hit_reg_plane(ray, scene, bvh_ret->t);
		if (!plane_hit)
			return (bvh_ret);
		return (plane_hit);
	}
	return (hit_reg_plane(ray, scene, FLT_MAX));
}

float	pass_through_no_refract(t_ray *ray, t_object *obj);

t_rgb	hit_register_light(t_ray *ray, t_data *data, t_vec3 light_pos)
{
	t_rgb		transparency;
	float		light_distance;
	t_object	*object;

	transparency = rgb(1, 1, 1);
	light_distance = vec3_length(vec3_sub(light_pos, ray->origin));
	object = hit_register(ray, &data->scene);
	if (!object)
		return (transparency);
	light_distance -= object->t + EPSILON;
	apply_mat(ray, object, &data->params, data);
	while (light_distance > 0)
	{
		t_rgb	temp = ray->hit_rgb;
		temp = rgb_scale(temp, 1 - ray->hit_opacity);
		transparency = rgb_mult(transparency, temp);
		object = hit_register(ray, &data->scene);
		if (!object)
			return (transparency);
		apply_mat(ray, object, &data->params, data);
		object->t += pass_through_no_refract(ray, object);
		light_distance -= object->t + EPSILON;
	}
	return (transparency);
}
