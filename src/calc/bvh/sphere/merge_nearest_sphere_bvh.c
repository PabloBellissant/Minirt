/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_nearest_sphere_bvh.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 05:05:26 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/12 05:05:55 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "float.h"
#include "bvh.h"

void	merge_nearest_sphere_bvh(t_vector *bvh_vec, int *parents)
{
	size_t			best[2];
	size_t			i[2];
	float			min_area;
	float			actual_area;
	t_sphere_bvh	*bvh;

	bvh = bvh_vec->data;
	min_area = FLT_MAX;
	best[0] = 0;
	best[1] = 0;
	i[0] = 0;
	while (i[0] < bvh_vec->num_elements)
	{
		i[1] = i[0] + 1;
		while (i[1] < bvh_vec->num_elements)
		{
			if (parents[i[0]] == 0 && parents[i[1]] == 0)
			{
				actual_area = get_next_sphere_bvh_area(&bvh[i[0]], &bvh[i[1]]);
				if (actual_area < min_area)
				{
					min_area = actual_area;
					best[0] = i[0];
					best[1] = i[1];
				}
			}
			++i[1];
		}
		++i[0];
	}
	merge_sphere_bvh(bvh_vec, best[0], best[1]);
	parents[best[0]] = 1;
	parents[best[1]] = 1;
}
