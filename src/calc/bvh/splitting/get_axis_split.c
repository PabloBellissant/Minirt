/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_axis_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:10:49 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/04 23:29:10 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

static inline t_axis	get_axis_largest_spread(const t_vec3 spread)
{
	if ((spread.x > spread.y) && (spread.x > spread.z))
		return (X_AXIS);
	else if (spread.y > spread.z)
		return (Y_AXIS);
	return (Z_AXIS);
}

static inline t_axis	get_axis_split_sphere(const t_vector primitives)
{
	return (get_axis_largest_spread(get_primitives_variance(primitives)));
}

static inline t_axis	get_axis_split_aabb(const t_bvh_aabb parent_aabb)
{
	return (get_axis_largest_spread(get_cuboid_extent(parent_aabb.cuboid)));
}

static inline t_axis	get_axis_split_obb(const t_bvh_obb parent_obb,
							const t_vector primitives)
{
	return (get_axis_largest_spread(get_obb_projected_spread(parent_obb,
				primitives)));
}

/*
	Returns the axis with the largest extent to split
*/
t_axis	get_axis_split(const t_bvh_header *bvh_header,
			const t_bvh_bounds parent_bounds, const t_vector primitives)
{
	if (bvh_header->shape == BVH_SPHERE)
		return (get_axis_split_sphere(primitives));
	else if (bvh_header->shape == BVH_AABB)
		return (get_axis_split_aabb(parent_bounds.aabb));
	else if (bvh_header->shape == BVH_OBB)
		return (get_axis_split_obb(parent_bounds.obb, primitives));
	return (X_AXIS);
}
