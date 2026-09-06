/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   med_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 04:41:21 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/04 23:38:27 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

size_t	get_med_space(const t_bvh_header *bvh_header,
			const t_bvh_bounds parent_bounds, const t_vector primitives);

int	med_space(const t_bvh_header *bvh_header, const t_bvh_bounds parent_bounds,
	const t_vector prim, t_vector child_prim[BVH_LR])
{
	size_t				left_count;
	size_t				right_count;
	t_vector			primitives;

	vector_copy(&primitives, &prim);
	left_count = get_med_space(bvh_header, parent_bounds, primitives);
	right_count = primitives.num_elements - left_count;
	return (try_split(primitives, child_prim, left_count, right_count));
}
