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

int	merge_nearest_bvh(t_vector *bvh_vec)
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
			ft_memcpy(best, i_old, sizeof(size_t) * 2);
		}
		i_old[0] = i_old[1];
		i_old[1] = get_next_no_parent(i_old[1], bvh, bvh_vec->num_elements - 1);
	}
	if (min_area >= FLT_MAX)
		return (0);
	return (merge_bvh(bvh_vec, &bvh[best[0]], &bvh[best[1]]) == -1);
}

size_t	get_next_no_parent(ssize_t actual, t_bvh *bvh, ssize_t max)
{
	++actual;
	while ((actual < max) && (bvh[actual].parent != NULL))
		++actual;
	return (actual);
}
