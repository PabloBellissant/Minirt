/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_bounds_aabb.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 18:44:26 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 14:23:31 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

static inline t_bvh_aabb	get_sphere_aabb_bounds(t_sphere sphere)
{
	return ((t_bvh_aabb){
		.min = vec3_sub_scalar(sphere.centroid, sphere.radius),
		.max = vec3_add_scalar(sphere.centroid, sphere.radius)
	});
}

static inline t_bvh_aabb	get_triangle_aabb_bounds(t_triangle triangle)
{
	t_bvh_aabb	largest;

	largest.cuboid = cuboid_inf();
	largest.cuboid = get_point_cuboid_union(largest.cuboid, triangle.p0.pos);
	largest.cuboid = get_point_cuboid_union(largest.cuboid, triangle.p1.pos);
	largest.cuboid = get_point_cuboid_union(largest.cuboid, triangle.p2.pos);
	return (largest);
}

static inline t_bvh_aabb	get_prim_aabb_bounds(t_object obj)
{
	if (obj.type == SPHERE)
		return (get_sphere_aabb_bounds(obj.sphere));
	else if (obj.type == TRIANGLE)
		return (get_triangle_aabb_bounds(obj.triangle));
	return ((t_bvh_aabb){.cuboid = cuboid_zero()});
}

void	evaluate_bounds_aabb(t_bvh_aabb *new, t_vector primitives)
{
	size_t		i;
	t_object	*objects;

	new->cuboid = cuboid_inf();
	i = 0;
	objects = primitives.data;
	while (i < primitives.num_elements)
	{
		new->cuboid = get_cuboid_union(new->cuboid,
				get_prim_aabb_bounds(objects[i]).cuboid);
		i++;
	}
}
