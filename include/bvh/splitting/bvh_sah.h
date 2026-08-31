/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_sah.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:18:05 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/05 03:18:23 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_SAH_H
# define BVH_SAH_H

# include "bvh_build_utils.h"
# include "bvh_shape.h"

# define SAH_NUM_BINS 16
# define SAH_CT 1.0f
# define SAH_CI 1.0f
# define SAH_SM 1e30f

typedef struct s_bvh_header	t_bvh_header;
typedef union u_bvh_bounds	t_bvh_bounds;

typedef struct s_sah_bucket
{
	ssize_t			count;
	t_bvh_bounds	bounds;
}					t_sah_bucket;

typedef struct s_sah_plan
{
	int			split_bin;
	t_axis		axis;
	t_vec3		cmin_proj;
	float		inv_extent;
	float		cost;
	t_bvh_shape	bvh_shape;
}				t_sah_plan;

t_bvh_bounds	sah_merge_bounds(const t_bvh_shape bvh_shape,
					const t_bvh_bounds a, const t_bvh_bounds b);

#endif//BVH_SAH_H
