/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obb_projected_spread.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 02:43:51 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/04 23:27:23 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

t_vec3	get_obb_projected_spread(const t_bvh_obb obb, const t_vector primitives)
{
	t_cuboid	extent;
	t_axis		axis;
	size_t		i;
	float		p;

	extent = cuboid_inf();
	i = 0;
	while (i < primitives.num_elements)
	{
		axis = X_AXIS;
		while (axis < NUM_AXIS)
		{
			p = vec3_dot(((t_object *)get_vector_value(&primitives,
							i))->centroid, obb.axes[axis]);
			extent.min.s[axis] = fminf(extent.min.s[axis], p);
			extent.max.s[axis] = fmaxf(extent.max.s[axis], p);
			axis++;
		}
		i++;
	}
	return (get_cuboid_extent(extent));
}
