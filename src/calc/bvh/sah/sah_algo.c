/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sah_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 13:07:23 by jaubry--          #+#    #+#             */
/*   Updated: 2026/01/20 14:45:47 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_sah.h"

// For each axis, build bins and evaluate SAH
int choose_sah_split(t_vector *index_vec, t_aabb_bvh *parent_bvh,
						   t_object *objects, int *out_axis, int *out_bin)
{
	int		axis;
	t_vec3	cmin;
	t_vec3	cmax;
	float	extent;
	t_bin	bins[NUM_BINS];
	float	best_cost = SM;

	get_sah_centroid_bounds(index_vec, objects, &cmin, &cmax);
	axis = -1;
	while (axis < 3 - 1)
	{
		axis++;
		extent = (&cmax.x)[axis] - (&cmin.x)[axis];
		if (extent <= 0.0f)
			continue;
		ft_bzero(bins, sizeof(bins));
		fill_bins(axis, cmin, ((float)NUM_BINS / extent), index_vec, objects, bins);

		int	best_axis = -1;
		int	best_bin = -1;
		get_axis_and_bin(axis, &best_axis, &best_bin, bins, parent_bvh, &best_cost);
		if (best_axis != -1)
		{
			*out_axis = best_axis;
			*out_bin = best_bin;
		}
	}
	return (*out_axis != -1);
}
