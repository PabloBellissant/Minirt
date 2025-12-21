/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color_through.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 04:16:00 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/17 04:16:00 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <float.h>
#include "calc.h"

t_rgb	get_color_through_object(t_ray *ray, t_scene *scene, float light_distance)
{
	t_object	*bvh_hit;
	t_object	*plane_hit;

	bvh_hit = hit_aabb_bvh(ray, scene->bvh.aabb_bvh);
	if (bvh_hit && bvh_hit->t < light_distance)
	{
		plane_hit = hit_reg_plane(ray, scene, bvh_hit->t);
		if (plane_hit)
			bvh_hit = plane_hit;
	}
	else
		bvh_hit = hit_reg_plane(ray, scene, light_distance);
	if (bvh_hit && bvh_hit->t < light_distance)
	{
	// 	hits[pixel].hit_obj = bvh_hit;
	// 	hits[pixel].hit = true;
	// 	hits[pixel].mat_id = bvh_hit->mat_id;
	// 	hits[pixel].hit_point = vec3_add(rays->origin,
	// 							 vec3_scale(rays->dir, bvh_hit->t));
	// 	fill_uv_normal(hits[pixel].hit_point, bvh_hit,
	// 		&hits[pixel].uv, &hits[pixel].normal);
		return (rgb(0, 0, 0));
	}
	return (rgb(1, 1, 1));
}

//
// void	intersect_scene(t_ray *rays, t_hit *hits, t_scene *scene, int pixel)
// {
// 	t_object	*bvh_hit;
// 	t_object	*plane_hit;
//
// 	rays = &rays[hits[pixel].id];
// 	bvh_hit = hit_aabb_bvh(rays, scene->bvh.aabb_bvh);
// 	if (bvh_hit)
// 	{
// 		plane_hit = hit_reg_plane(rays, scene, bvh_hit->t);
// 		if (plane_hit)
// 			bvh_hit = plane_hit;
// 	}
// 	else
// 		bvh_hit = hit_reg_plane(rays, scene, FLT_MAX);
// 	if (bvh_hit)
// 	{
// 		hits[pixel].hit_obj = bvh_hit;
// 		hits[pixel].hit = true;
// 		hits[pixel].mat_id = bvh_hit->mat_id;
// 		hits[pixel].hit_point = vec3_add(rays->origin,
// 								 vec3_scale(rays->dir, bvh_hit->t));
// 		fill_uv_normal(hits[pixel].hit_point, bvh_hit,
// 			&hits[pixel].uv, &hits[pixel].normal);
// 		return ;
// 	}
// 	hits[pixel].hit = false;
// 	fill_skybox_uv(&rays->dir, &hits[pixel].uv);
// }
