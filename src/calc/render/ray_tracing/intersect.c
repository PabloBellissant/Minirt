/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 03:54:30 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/14 00:06:30 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>

#include "calc.h"
#include "minirt.h"
#include "vec3_operations.h"

void	intersect_scene(t_ray *rays, t_hit *hits, t_scene *scene, int pixel)
{
	t_object	*bvh;
	t_object	*plane_hit;

	rays = &rays[hits[pixel].id];
	bvh = hit_aabb_bvh(rays, scene->bvh.aabb_bvh);
	if (bvh)
	{
		plane_hit = hit_reg_plane(rays, scene, bvh->t);
		if (plane_hit)
			bvh = plane_hit;
	}
	else
		bvh = hit_reg_plane(rays, scene, FLT_MAX);
	hits[pixel].hit = (bvh != NULL);
	if (!bvh)
	{
		fill_skybox_uv(&rays->dir, &hits[pixel].uv);
		return ;
	}
	hits[pixel].hit_obj = bvh;
	hits[pixel].mat_id = bvh->mat_id;
	hits[pixel].hit_point = vec3_add(rays->origin,
			vec3_scale(rays->dir, bvh->t));
	fill_uv_normal(hits[pixel].hit_point, bvh,
		&hits[pixel].uv, &hits[pixel].normal);
}

void	intersect_loop(t_ray *rays, t_hit *hits, t_scene *scene, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		intersect_scene(rays, hits, scene, i);
		++i;
	}
}
