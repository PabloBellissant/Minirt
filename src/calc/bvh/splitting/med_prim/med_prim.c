/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   med_prim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 14:49:05 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/04 23:36:20 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

/*
	Splitting algorithm that splits always to have an equal amount of
	primitives between each sides. 
	Will choose the split axis that has the biggest spread.
*/
int	med_prim(const t_bvh_header *bvh_header, const t_bvh_bounds parent_bounds,
		const t_vector prim, t_vector child_prim[BVH_LR])
{
	const size_t		median = prim.num_elements / 2;
	const size_t		right_count = prim.num_elements - median;
	t_vector			primitives;
	t_axis				axis;

	vector_copy(&primitives, &prim);
	axis = get_axis_split(bvh_header, parent_bounds, primitives);
	sort_prim(bvh_header, parent_bounds, primitives, axis);
	return (try_split(primitives, child_prim, median, right_count));
}
