/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_obj_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:22:27 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/04 23:29:33 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

static inline float	key_dir(const t_object obj, const t_vec3 axes)
{
	return (vec3_dot(obj.centroid, axes));
}

static inline float	key_axis(const t_object obj, const t_axis axis)
{
	return (obj.centroid.s[axis]);
}

float	key_obj(const t_bvh_shape bvh_shape, const t_bvh_bounds parent_bounds,
			const t_object obj, const t_axis axis)
{
	if (bvh_shape == BVH_OBB)
		return (key_dir(obj, parent_bounds.obb.axes[axis]));
	return (key_axis(obj, axis));
}
