/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_uv_normal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 05:02:30 by pabellis          #+#    #+#             */
/*   Updated: 2026/01/04 05:02:30 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "calc.h"

void	fill_skybox_uv(const t_vec3 *dir, t_vec2 *uv)
{
	uv->u = 0.5f + atan2f(dir->z, dir->x) / (2.0f * M_PI);
	uv->v = 0.5f - asinf(dir->y) / M_PI;
}

static void	fill_sphere_uv_normal(t_vec3 hit_point, t_sphere *sphere,
			t_vec2 *uv, t_vec3 *norm)
{
	*norm = vec3_sub(hit_point, sphere->pos);
	*norm = vec3_normalize(*norm);
	uv->u = 0.5f + atan2f(norm->z, norm->x) / (2.0f * M_PI);
	uv->v = 0.5f + asinf(norm->y) / M_PI;
}

static void	fill_plane_uv_normal(t_vec3 hit_point, t_plane *plane,
			t_vec2 *uv, t_vec3 *norm)
{
	t_vec3	local_point;

	local_point = vec3_sub(hit_point, plane->pos);
	uv->u = vec3_dot(local_point, plane->tangent) * plane->texture_scaling;
	uv->v = vec3_dot(local_point, plane->bitangent) * plane->texture_scaling;
	*norm = plane->normal;
}

static void	fill_triangle_uv_normal(t_vec3 hit_point, t_triangle *t,
			t_vec2 *uv, t_vec3 *norm)
{
	t_vec3	bary;
	float	d20;
	float	d21;

	hit_point = vec3_sub(hit_point, t->p0.pos);
	d20 = vec3_dot(hit_point, t->edge_p1p0);
	d21 = vec3_dot(hit_point, t->edge_p2p0);
	bary.v = (t->d11 * d20 - t->d01 * d21) / t->denom;
	bary.w = (t->d00 * d21 - t->d01 * d20) / t->denom;
	bary.u = 1.0f - bary.v - bary.w;
	uv->u = bary.u * t->p0.uv.u
		+ bary.v * t->p1.uv.u
		+ bary.w * t->p2.uv.u;
	uv->v = bary.u * t->p0.uv.v
		+ bary.v * t->p1.uv.v
		+ bary.w * t->p2.uv.v;
	*norm = vec3_add(vec3_add(
				vec3_scale(t->p0.norm, bary.u),
				vec3_scale(t->p1.norm, bary.v)),
			vec3_scale(t->p2.norm, bary.w));
	*norm = vec3_normalize(*norm);
}

void	fill_uv_normal(t_vec3 hit_point, t_object *object,
				t_vec2 *uv, t_vec3 *norm)
{
	if (object->type == TRIANGLE)
		fill_triangle_uv_normal(hit_point, &object->triangle, uv, norm);
	else if (object->type == PLANE)
		fill_plane_uv_normal(hit_point, &object->plane, uv, norm);
	else if (object->type == SPHERE)
		fill_sphere_uv_normal(hit_point, &object->sphere, uv, norm);
	uv->u -= floor(uv->u);
	uv->v -= floor(uv->v);
	uv->v = 1.0f - uv->v;
}


