/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_shape.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:20:07 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/05 01:46:54 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_SHAPE_H
# define BVH_SHAPE_H

# include "bvh_build_utils.h"

typedef enum e_bvh_shape
{
	BVH_SPHERE,
	BVH_AABB,
	BVH_OBB
}	t_bvh_shape;

typedef struct s_bvh_header		t_bvh_header;
typedef struct s_bvh_build_pack	t_bvh_build_pack;

void	evaluate_bounds(const t_bvh_shape bvh_shape, t_bvh_build_pack *child);

#endif//BVH_SHAPE_H
