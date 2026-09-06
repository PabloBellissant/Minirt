/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_splitting.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:20:32 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/05 01:48:45 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_SPLITTING_H
# define BVH_SPLITTING_H

# include "bvh_med_prim.h"
# include "bvh_med_space.h"
# include "bvh_sah.h"
# include "bvh_build_utils.h"
# include "bvh_shape.h"

typedef enum e_bvh_split
{
	MED_PRIM,
	MED_SPACE,
	SAH
}	t_bvh_split;

void	sort_prim(const t_bvh_header *bvh_header,
			const t_bvh_bounds parent_bounds, t_vector primitives,
			const t_axis axis);
float	key_obj(const t_bvh_shape bvh_shape, const t_bvh_bounds parent_bounds,
			const t_object obj, const t_axis axis);
int		try_split(t_vector primitives, t_vector child_prim[BVH_LR],
			size_t left_count, size_t right_count);

int		med_prim(const t_bvh_header *bvh_header,
			const t_bvh_bounds parent_bounds, const t_vector prim,
			t_vector child_prim[BVH_LR]);
int		med_space(const t_bvh_header *bvh_header,
			const t_bvh_bounds parent_bounds, const t_vector prim,
			t_vector child_prim[BVH_LR]);
int		sah(const t_bvh_header *bvh_header,
			const t_bvh_bounds parent_bounds, const t_vector prim,
			t_vector child_prim[BVH_LR]);

int		evaluate_split(const t_bvh_header *bvh_header,
			const t_bvh_bounds cur_bounds, const t_vector primitives,
			t_bvh_build_pack child[BVH_LR]);

#endif//BVH_SPLITTING_H
