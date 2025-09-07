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

void	merge_nearest_bvh(t_vector *bvh_vec, int *parents)
{
	size_t	best[2];
	size_t	i[2];
	float	min_area;
	float	actual_area;
	t_bvh	*bvh;

	bvh = bvh_vec->data;
	min_area = FLT_MAX;
	i[0] = 0;
	while (i[0] < bvh_vec->num_elements)
	{
		if (parents[i[0]] == 0)
		{
			i[1] = i[0] + 1;
			while (i[1] < bvh_vec->num_elements)
			{
				if (parents[i[1]] == 0)
				{
					actual_area = get_next_bvh_area(&bvh[i[0]], &bvh[i[1]]);
					if (actual_area < min_area)
					{
						min_area = actual_area;
						best[0] = i[0];
						best[1] = i[1];
					}
				}
				++i[1];
			}
		}
		++i[0];
	}
	merge_bvh(bvh_vec, best[0], best[1]);
	parents[best[0]] = 1;
	parents[best[1]] = 1;
}
