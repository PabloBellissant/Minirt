/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_build_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 02:44:28 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/12 01:08:52 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_BUILD_UTILS_H
# define BVH_BUILD_UTILS_H

# include "bvh_bounds.h"
# include "bvh_shape.h"
# include "libft.h"

typedef enum e_axis
{
	X_AXIS,
	Y_AXIS,
	Z_AXIS,
	NUM_AXIS
}	t_axis;

typedef enum e_bvh_child
{
	BVH_L = 0,
	BVH_R,
	BVH_LR
}	t_bvh_child;

typedef struct s_sort_params
{
	t_bvh_shape		shape;
	t_bvh_bounds	bounds;
	t_axis			axis;
	t_object		*a;
	size_t			n;
}					t_sort_params;

typedef struct s_bvh_build_pack
{
	t_bvh_bounds	bounds;
	t_vector		primitives;
}	t_bvh_build_pack;

t_axis	get_axis_split(const t_bvh_header *bvh_header,
			const t_bvh_bounds parent_bounds, const t_vector primitives);

#endif//BVH_BUILD_UTILS_H
