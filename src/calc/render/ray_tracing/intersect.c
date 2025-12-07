/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 03:54:30 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/02 03:54:35 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>

#include "calc.h"

static void	fill_uv_normal(t_vec3 hit_point, t_object *object, t_vec2 *uv, t_vec3 *norm);
static void	fill_skybox_uv(const t_vec3 *dir, t_vec2 *uv);

void	intersect_scene(t_ray *rays, t_hit *hits, t_scene *scene, int pixel)
{
	t_object	*bvh_hit;
	t_object	*plane_hit;

	hits[pixel].id = pixel;
	bvh_hit = hit_aabb_bvh(rays + pixel, scene->bvh.aabb_bvh);
	if (bvh_hit)
	{
		plane_hit = hit_reg_plane(rays + pixel, scene, bvh_hit->t);
		if (plane_hit)
			bvh_hit = plane_hit;
	}
	else
		bvh_hit = hit_reg_plane(rays + pixel, scene, FLT_MAX);
	if (bvh_hit)
	{
		hits[pixel].hit = true;
		hits[pixel].mat_id = bvh_hit->mat_id;
		hits[pixel].hit_point = vec3_add(rays[pixel].origin,
								 vec3_scale(rays[pixel].dir, bvh_hit->t));
		fill_uv_normal(hits[pixel].hit_point, bvh_hit,
			&hits[pixel].uv, &hits[pixel].normal);
		hits[pixel].hit_point = vec3_add(hits[pixel].hit_point, vec3_scale(hits[pixel].normal, 0.01f));
		return ;
	}
	hits[pixel].hit = false;
	fill_skybox_uv(&rays[pixel].dir, &hits[pixel].uv);
}

static void	fill_skybox_uv(const t_vec3 *dir, t_vec2 *uv)
{
	uv->u = 0.5f + atan2f(dir->z, dir->x) / (2.0f * M_PIf);
	uv->v = 0.5f + asinf(dir->y) / M_PIf;
}

static void	fill_uv_normal(t_vec3 hit_point, t_object *object, t_vec2 *uv, t_vec3 *norm)
{
	t_vec3	bary;
	t_vec3	local_point;

	if (object->type == TRIANGLE)
	{
		t_vec3	n0, n1, n2;

		t_vec3 v0v1 = object->triangle.edge_p1p0;
		t_vec3 v0v2 = object->triangle.edge_p2p0;
		t_vec3 v0p = vec3_sub(hit_point, object->triangle.p0.pos);
		float d00 = vec3_dot(v0v1, v0v1);
		float d01 = vec3_dot(v0v1, v0v2);
		float d11 = vec3_dot(v0v2, v0v2);
		float d20 = vec3_dot(v0p, v0v1);
		float d21 = vec3_dot(v0p, v0v2);

		float denom = d00 * d11 - d01 * d01;
		bary.v = (d11 * d20 - d01 * d21) / denom;
		bary.w = (d00 * d21 - d01 * d20) / denom;
		bary.u = 1.0f - bary.v - bary.w;

		uv->u = bary.u * object->triangle.p0.uv.u +
					  bary.v * object->triangle.p1.uv.u +
					  bary.w * object->triangle.p2.uv.u;

		uv->v = bary.u * object->triangle.p0.uv.v +
					  bary.v * object->triangle.p1.uv.v +
					  bary.w * object->triangle.p2.uv.v;
		n0 = vec3_scale(object->triangle.p0.norm, bary.u);
		n1 = vec3_scale(object->triangle.p1.norm, bary.v);
		n2 = vec3_scale(object->triangle.p2.norm, bary.w);
		*norm = vec3_add(n0, vec3_add(n1, n2));
		*norm = vec3_normalize(*norm);
	}
	else if (object->type == PLANE)
	{
		local_point = vec3_sub(hit_point, object->plane.pos);
		uv->u = vec3_dot(local_point, object->plane.tangent) * 0.1f;
		uv->v = vec3_dot(local_point, object->plane.bitangent) * 0.1f;
		*norm = object->plane.normal;
		*norm = vec3_normalize(*norm);
	}
	else if (object->type == SPHERE)
	{
		*norm = vec3_sub(hit_point, object->sphere.pos);
		*norm = vec3_normalize(*norm);
		uv->u = 0.5f + atan2f(norm->z, norm->x) / (2.0f * M_PIf);
		uv->v = 0.5f + asinf(norm->y) / M_PIf;
	}
}

