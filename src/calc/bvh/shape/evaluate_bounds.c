/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_bounds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:26:42 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/03 00:27:54 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

void	evaluate_bounds_sphere(t_bvh_sphere *new, t_vector primitives);
void	evaluate_bounds_aabb(t_bvh_aabb *new, t_vector primitives);
void	evaluate_bounds_obb(t_bvh_obb *new, t_vector primitives);

void	evaluate_bounds(const t_bvh_shape bvh_shape, t_bvh_build_pack *child)
{
	if (bvh_shape == BVH_SPHERE)
		evaluate_bounds_sphere(&child->bounds.sphere, child->primitives);
	else if (bvh_shape == BVH_AABB)
		evaluate_bounds_aabb(&child->bounds.aabb, child->primitives);
	else if (bvh_shape == BVH_OBB)
		evaluate_bounds_obb(&child->bounds.obb, child->primitives);
}
