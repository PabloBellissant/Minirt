/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_register.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 00:47:55 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/09 22:45:48 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>

#include "vectors.h"
#include "calc.h"
#include "minirt.h"

#define OFFSET 0.001f

unsigned int sample_texture(t_texture *texture, float u, float v)
{
	t_rgb_int	rgb;
	int			x;
	int			y;
	int			offset;

	x = (int)(u * (float)(texture->width));
	y = (int)(v * (float)(texture->height));
	offset = y * texture->tex_size_line + x * (texture->tex_bpp / 8);
	ft_memcpy(&rgb.rgb, texture->pixels + offset, sizeof(unsigned int));
	return (rgb.rgb);
}

float	sample_binary_texture(t_texture *texture, float u, float v)
{
	int				x;
	int				y;
	int				offset;
	unsigned char	pixel;

	x = (int)(u * (float)(texture->width));
	y = (int)(v * (float)(texture->height));
	offset = y * texture->tex_size_line + x;
	pixel = texture->pixels[offset];
	return ((float)pixel / 255.0f);
}


t_vec3	texture_to_vec3(unsigned int color)
{
	t_vec3 result;

	result.z = (float)((color >> 16) & 0xFF) / 255.0f;
	result.y = (float)((color >> 8) & 0xFF) / 255.0f;
	result.x = (float)(color & 0xFF) / 255.0f;

	return result;
}

t_vec3 apply_normalmap(t_vec3 hit_normal, t_vec3 nmap, t_vec3 tangent, t_vec3 bitangent)
{
	t_vec3	n_tangent;

	n_tangent = vec3_sub(vec3_scale(nmap, 2.0f), vec3(1, 1, 1));
	t_vec3 tx = vec3_scale(tangent, n_tangent.x);
	t_vec3 ty = vec3_scale(bitangent, n_tangent.y);
	t_vec3 tz = vec3_scale(hit_normal, n_tangent.z);

	t_vec3 n_world = vec3_add(vec3_add(tx, ty), tz);
	n_world = vec3_normalize(n_world);

	return n_world;
}

t_vec3	get_tangent(t_vec3 n)
{
	t_vec3 up;

	if (fabsf(n.y) > 0.999f)
		up = vec3(1, 0, 0);
	else
		up = vec3(0, 1, 0);
	return (vec3_normalize(vec3_cross(up, n)));
}

t_vec3 get_bitangent(t_vec3 n, t_vec3 tangent)
{
	return (vec3_cross(n, tangent));
}

t_vec3	sample_mat(t_ray *ray, t_vec2 uv, t_mat *mat)
{
	t_vec3	hit_point = vec3(0,0,0);
	t_rgb	nmap;
	t_vec3	tangent;
	t_vec3	new_normal;

	if (mat->map_kd)
	{
		ray->hit_rgb = texture_to_vec3(sample_texture(mat->map_kd, uv.x, uv.y));
		ray->hit_roughness = sample_binary_texture(mat->roughness_map, uv.x, uv.y);
		ray->hit_ambient = sample_binary_texture(mat->ambient_map, uv.x, uv.y);
		nmap = texture_to_vec3(sample_texture(mat->normal_map, uv.x, uv.y));
		tangent = get_tangent(ray->hit_normal);
		new_normal = apply_normalmap(ray->hit_normal, nmap, tangent, get_bitangent(ray->hit_normal, tangent));
		ray->hit_normal = new_normal;
	}
	else
	{
		ray->hit_rgb = mat->kd;
		ray->hit_roughness = 1.0f - mat->ks.x;
	}
	return (hit_point);
}

void	hit_register_obj(t_ray *restrict ray, t_object *restrict o, t_params *params)
{
	t_vec3	hit_point;
	t_vec3	axis;
	t_vec3	to_hit;
	t_vec2	uv;

	hit_point = vec3_scale(ray->dir, o->t);
	hit_point = vec3_add(ray->pos, hit_point);
	if (o->type == TRIANGLE)
	{
		t_vec3	n0, n1, n2;
		if (params->texture || params->smooth_shading)
		{
			t_vec3 v0v1 = vec3_sub(o->triangle.p1.pos, o->triangle.p0.pos);
			t_vec3 v0v2 = vec3_sub(o->triangle.p2.pos, o->triangle.p0.pos);
			t_vec3 v0p = vec3_sub(hit_point, o->triangle.p0.pos);

			float d00 = vec3_dot(v0v1, v0v1);
			float d01 = vec3_dot(v0v1, v0v2);
			float d11 = vec3_dot(v0v2, v0v2);
			float d20 = vec3_dot(v0p, v0v1);
			float d21 = vec3_dot(v0p, v0v2);

			float denom = d00 * d11 - d01 * d01;
			// Calcul des coordonnées barycentriques (UNE SEULE FOIS)
			float bary_v = (d11 * d20 - d01 * d21) / denom;
			float bary_w = (d00 * d21 - d01 * d20) / denom;
			float bary_u = 1.0f - bary_v - bary_w;

			// Interpolate texture coordinates
			float u_tex = bary_u * o->triangle.p0.uv.x +
						  bary_v * o->triangle.p1.uv.x +
						  bary_w * o->triangle.p2.uv.x;

			float v_tex = bary_u * o->triangle.p0.uv.y +
						  bary_v * o->triangle.p1.uv.y +
						  bary_w * o->triangle.p2.uv.y;


			unsigned int tex_color;
			if (o->mat.map_kd && params->texture)
			{
				tex_color = sample_texture(o->mat.map_kd, u_tex, 1 - v_tex);
				ray->hit_rgb = texture_to_vec3(tex_color);
				return ;
			}
			else
				ray->hit_rgb = o->triangle.rgb;
			n0 = vec3_scale(o->triangle.p0.norm, bary_u);
			n1 = vec3_scale(o->triangle.p1.norm, bary_v);
			n2 = vec3_scale(o->triangle.p2.norm, bary_w);
			ray->hit_normal = vec3_add(n0, vec3_add(n1, n2));
		}
		else
			ray->hit_normal = vec3_add(o->triangle.p0.norm, vec3_add(o->triangle.p1.norm, o->triangle.p2.norm));
		ray->hit_normal = unsafe_vec3_normalize(ray->hit_normal);

		if (params->texture)
		{
			ray->hit_rgb = texture_to_vec3(sample_texture(o->mat.map_kd, uv.x, uv.y));
			//ray->hit_roughness = sample_binary_texture(o->mat.roughness_map, uv.x, uv.y);
		}
		else
		{
			ray->hit_roughness = o->mat.ks.x;
			ray->hit_rgb = o->mat.kd;
		}
		hit_point = vec3_add(hit_point, vec3_scale(ray->hit_normal, EPSILON));
	}
	else if (o->type == SPHERE)
	{
		ray->hit_normal = vec3_sub(hit_point, o->sphere.pos);
		ray->hit_normal = unsafe_vec3_normalize(ray->hit_normal);
		uv.x = 0.5f + atan2f(ray->hit_normal.z, ray->hit_normal.x) / (2.0f * M_PIf);
		uv.y = 0.5f - asinf(ray->hit_normal.y) / M_PIf;

		hit_point = vec3_add(hit_point, vec3_scale(ray->hit_normal, EPSILON));
		sample_mat(ray, uv, &o->mat);
	}
	else if (o->type == PLANE)
	{
		ray->hit_normal = o->plane.normal;

		t_vec3 tangent, bitangent;

		tangent = get_tangent(o->plane.normal);
		bitangent = get_bitangent(o->plane.normal, tangent);
		bitangent = unsafe_vec3_normalize(bitangent);

		t_vec3 local_point = vec3_sub(hit_point, o->plane.pos);
		float u = vec3_dot(local_point, tangent) * 0.1f;
		float v = vec3_dot(local_point, bitangent) * 0.1f;

		u = u - floorf(u);
		v = v - floorf(v);

		hit_point = vec3_add(hit_point, vec3_scale(ray->hit_normal, EPSILON));
		sample_mat(ray, vec2(u, v), &o->mat);
	}
	else if (o->type == CYLINDER)
	{
		axis = o->cylinder.rot;
		to_hit = vec3_sub(hit_point, o->cylinder.pos);
		axis = vec3_scale(axis, vec3_dot(to_hit, axis));
		axis = vec3_add(o->cylinder.pos, axis);
		ray->hit_normal = vec3_sub(hit_point, axis);
		ray->hit_normal = unsafe_vec3_normalize(ray->hit_normal);
		ray->hit_rgb = o->cylinder.rgb;
		hit_point = vec3_add(hit_point, vec3_scale(ray->hit_normal, EPSILON));
	}
	ray->pos = hit_point;
	if (params->normal_debug)
		ray->hit_rgb = rgb_add_scalar(rgb_scale(ray->hit_normal, 0.5f), 0.5f);
}

t_object	*hit_sphere_bvh(t_ray *ray, t_sphere_bvh *bvh);

float	hit_register(t_ray *ray, t_data *data, t_object **hit_object)
{
	t_object	*bvh_ret;

	if (data->scene.bvh.bvh_mode == 0)
		bvh_ret = hit_sphere_bvh(ray, data->scene.bvh.sphere_bvh);
	else
		bvh_ret = hit_aabb_bvh(ray, data->scene.bvh.aabb_bvh);
	if (bvh_ret)
		(*hit_object) = hit_reg_plane(ray, &data->scene, bvh_ret->t);
	else
		(*hit_object) = hit_reg_plane(ray, &data->scene, FLT_MAX);
	if (bvh_ret != NULL)
	{
		if (!(*hit_object) || bvh_ret->t < (*hit_object)->t)
			(*hit_object) = bvh_ret;
	}
	else if (!(*hit_object) || (*hit_object)->t >= FLT_MAX)
		return (-1.f);
	hit_register_obj(ray, (*hit_object), &data->params);
	return ((*hit_object)->t);
}
