/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_nearest_bvh.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 03:11:49 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/31 21:12:31 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "bvh.h"
#include <float.h>

size_t	get_next_no_parent(ssize_t actual, t_bvh *bvh, ssize_t max);

int	merge_nearest_bvh(t_vector *bvh_vec)
{
	size_t	best[2];
	size_t	i;
	size_t	old;
	float	min_area;
	float	actual_area;
	t_bvh	*bvh;

	bvh = bvh_vec->data;
	min_area = FLT_MAX;
	old = get_next_no_parent(-1, bvh, bvh_vec->num_elements - 1);
	i = get_next_no_parent(old, bvh, bvh_vec->num_elements - 1);
	while (i < bvh_vec->num_elements)
	{
		actual_area = get_next_bvh_area(&bvh[old], &bvh[i]);
		if (actual_area < min_area)
		{
			min_area = actual_area;
			best[0] = old;
			best[1] = i;
		}
		old = i;
		i = get_next_no_parent(i, bvh, bvh_vec->num_elements - 1);
	}
	if (min_area >= FLT_MAX)
		return (0);
	if (merge_bvh(bvh_vec, &bvh[best[0]], &bvh[best[1]]) == -1)
		return (-1);
	return (0);
}

size_t	get_next_no_parent(ssize_t actual, t_bvh *bvh, ssize_t max)
{
	++actual;
	while ((actual < max) && (bvh[actual].parent != NULL))
		++actual;
	return (actual);
}
