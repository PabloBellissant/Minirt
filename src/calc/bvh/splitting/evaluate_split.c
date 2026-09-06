/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 12:50:01 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/04 23:29:25 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

/*
	-1: error
	0: internal node
	1: object ?
*/
int	evaluate_split(const t_bvh_header *bvh_header,
		const t_bvh_bounds cur_bounds, const t_vector primitives,
		t_bvh_build_pack child[BVH_LR])
{
	t_vector	child_prim[BVH_LR];

	ft_bzero(child_prim, sizeof(child_prim));
	if (bvh_header->splitting_algo == MED_PRIM)
	{
		if (med_prim(bvh_header, cur_bounds, primitives, child_prim) != 0)
			return (-1);
	}
	else if (bvh_header->splitting_algo == MED_SPACE)
	{
		if (med_space(bvh_header, cur_bounds, primitives, child_prim) != 0)
			return (-1);
	}
	else if (bvh_header->splitting_algo == SAH)
	{
		if (sah(bvh_header, cur_bounds, primitives, child_prim) != 0)
			return (-1);
	}
	else
		return (-1);
	child[BVH_L].primitives = child_prim[BVH_L];
	child[BVH_R].primitives = child_prim[BVH_R];
	return (0);
}
