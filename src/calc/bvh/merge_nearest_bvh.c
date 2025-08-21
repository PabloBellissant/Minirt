/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_nearest_bvh.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 03:11:49 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 05:13:12 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include <float.h>

size_t	get_next_no_parent(ssize_t actual, t_bvh *bvh, ssize_t max);

void	merge_nearest_bvh(t_vector *bvh_vec)
{
	size_t	best[2];
	size_t	i_old[2];
	float	min_area;
	float	actual_area;
	t_bvh	*bvh;

	bvh = bvh_vec->data;
	min_area = FLT_MAX;
	i_old[0] = get_next_no_parent(-1, bvh, bvh_vec->num_elements - 1);
	i_old[1] = get_next_no_parent(i_old[0], bvh, bvh_vec->num_elements - 1);
	while (i_old[1] < bvh_vec->num_elements)
	{
		actual_area = get_next_bvh_area(&bvh[i_old[0]], &bvh[i_old[1]]);
		if (actual_area < min_area)
		{
			min_area = actual_area;
			best[0] = i_old[0];
			best[1] = i_old[1];
		}
		i_old[0] = i_old[1];
		i_old[1] = get_next_no_parent(i_old[1], bvh, bvh_vec->num_elements - 1);
	}
	merge_bvh(bvh_vec, best[0], best[1]);
}

size_t	get_next_no_parent(ssize_t actual, t_bvh *bvh, ssize_t max)
{
	++actual;
	while ((actual < max) && (bvh[actual].parent != NULL))
		++actual;
	return (actual);
}
