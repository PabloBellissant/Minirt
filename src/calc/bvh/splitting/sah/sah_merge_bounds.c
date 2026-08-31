/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sah_merge_bounds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 04:12:50 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/04 23:34:02 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

static inline t_cuboid	get_merged_obb_bounds(const t_bvh_obb a,
							const t_bvh_obb b)
{
	t_cuboid	extent_a;
	t_cuboid	extent_b;
	float		center_a;
	float		center_b;
	t_axis		axis;

	axis = X_AXIS;
	while (axis < NUM_AXIS)
	{
		center_a = vec3_dot(a.center, a.axes[axis]);
		center_b = vec3_dot(b.center, a.axes[axis]);
		extent_a.min.s[axis] = center_a - a.half_extents.s[axis];
		extent_a.max.s[axis] = center_a + a.half_extents.s[axis];
		extent_b.min.s[axis] = center_b - b.half_extents.s[axis];
		extent_b.max.s[axis] = center_b + b.half_extents.s[axis];
		axis++;
	}
	return (get_cuboid_union(extent_a, extent_b));
}

static inline t_bvh_obb	sah_merge_obb(const t_bvh_obb a, const t_bvh_obb b)
{
	const t_cuboid	new = get_merged_obb_bounds(a, b);
	t_vec3			new_center;
	t_bvh_obb		out;
	t_axis			axis;

	out.q = a.q;
	ft_memcpy(&out.axes, &a.axes, sizeof(a.axes));
	out.half_extents = cuboid_half(new);
	new_center = cuboid_center(new);
	out.center = vec3_zero();
	axis = X_AXIS;
	while (axis < NUM_AXIS)
	{
		out.center = vec3_add(out.center,
				vec3_scale(out.axes[axis], new_center.s[axis]));
		axis++;
	}
	return (out);
}

static inline t_bvh_sphere	sah_merge_sphere(const t_bvh_sphere a,
								const t_bvh_sphere b)
{
	t_vec3	d;
	float	dist;
	float	new_r;
	float	t;
	t_vec3	c;

	d = vec3_sub(b.centroid, a.centroid);
	dist = vec3_length(d);
	if (a.radius >= (dist + b.radius))
		return (a);
	if (b.radius >= (dist + a.radius))
		return (b);
	new_r = (dist + a.radius + b.radius) * 0.5f;
	if (dist <= 0.0f)
		c = a.centroid;
	else
	{
		t = (new_r - a.radius) / dist;
		c = vec3_add(a.centroid, vec3_scale(d, t));
	}
	return ((t_bvh_sphere){.pos = c, .radius = new_r});
}

t_bvh_bounds	sah_merge_bounds(const t_bvh_shape bvh_shape,
					const t_bvh_bounds a, const t_bvh_bounds b)
{
	t_bvh_bounds	out;

	ft_bzero(&out, sizeof(out));
	if (bvh_shape == BVH_SPHERE)
		out.sphere = sah_merge_sphere(a.sphere, b.sphere);
	else if (bvh_shape == BVH_AABB)
		out.aabb.cuboid = get_cuboid_union(a.aabb.cuboid, b.aabb.cuboid);
	else if (bvh_shape == BVH_OBB)
		out.obb = sah_merge_obb(a.obb, b.obb);
	return (out);
}
