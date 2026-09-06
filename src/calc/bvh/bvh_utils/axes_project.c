/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   axes_project.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 01:31:28 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 14:24:03 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

t_vec3	axes_local_to_world(const t_vec3 axes[NUM_AXIS], const t_vec3 local)
{
	t_vec3	ret;
	t_axis	axis;

	ret = vec3_zero();
	axis = X_AXIS;
	while (axis < NUM_AXIS)
	{
		ret = vec3_add(ret, vec3_scale(axes[axis], local.s[axis]));
		axis++;
	}
	return (ret);
}

static inline void	project_point(t_cuboid *extent, const t_vec3 axes[NUM_AXIS],
						const t_vec3 p)
{
	t_axis	axis;
	float	v;

	axis = X_AXIS;
	while (axis < NUM_AXIS)
	{
		v = vec3_dot(p, axes[axis]);
		extent->min.s[axis] = fminf(extent->min.s[axis], v);
		extent->max.s[axis] = fmaxf(extent->max.s[axis], v);
		axis++;
	}
}

static inline void	project_triangle(t_cuboid *extent,
						const t_vec3 axes[NUM_AXIS], const t_triangle t)
{
	const t_vec3	tri_pts[3] = {t.p0.pos, t.p1.pos, t.p2.pos};
	size_t			tri_pt;

	tri_pt = 0;
	while (tri_pt < 3)
	{
		project_point(extent, axes, tri_pts[tri_pt]);
		tri_pt++;
	}
}

void	project_object(t_cuboid *extent, const t_object *obj,
			const t_vec3 axes[NUM_AXIS])
{
	*extent = cuboid_inf();
	if (obj->type == TRIANGLE)
		project_triangle(extent, axes, obj->triangle);
	else
		project_point(extent, axes, obj->centroid);
}
