/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sah_bins_cost.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 02:40:00 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/05 04:20:07 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

float			sah_cost(const t_bvh_header *bvh_header,
					const t_bvh_bounds parent_bounds,
					const t_sah_bucket sums[BVH_LR]);

static inline void	sah_sum_add(const t_bvh_header *bvh_header,
				t_sah_bucket *sum, const t_sah_bucket bin)
{
	if (bin.count > 0)
	{
		if (sum->count == 0)
			sum->bounds = bin.bounds;
		else
			sum->bounds = sah_merge_bounds(bvh_header->shape,
					sum->bounds, bin.bounds);
	}
	sum->count += bin.count;
}

static inline void	sah_split_sums(const t_bvh_header *bvh_header,
						const t_sah_bucket bins[SAH_NUM_BINS], const int split,
						t_sah_bucket sums[BVH_LR])
{
	size_t	i;

	sums[BVH_L].count = 0;
	sums[BVH_R].count = 0;
	i = 0;
	while (i <= (size_t)split)
	{
		sah_sum_add(bvh_header, &sums[BVH_L], bins[i]);
		i++;
	}
	i = (size_t)split + 1;
	while (i < SAH_NUM_BINS)
	{
		sah_sum_add(bvh_header, &sums[BVH_R], bins[i]);
		i++;
	}
}

float	sah_best_split_cost(const t_bvh_header *bvh_header,
			const t_bvh_bounds parent_bounds,
			const t_sah_bucket bins[SAH_NUM_BINS], t_sah_plan *plan)
{
	t_sah_bucket	sums[BVH_LR];
	float			best_cost;
	int				split;

	best_cost = SAH_SM;
	plan->split_bin = -1;
	split = 0;
	while (split < (SAH_NUM_BINS - 1))
	{
		sah_split_sums(bvh_header, bins, split, sums);
		if ((sums[BVH_L].count > 0) && (sums[BVH_R].count > 0))
		{
			plan->cost = sah_cost(bvh_header, parent_bounds, sums);
			if (plan->cost < best_cost)
			{
				best_cost = plan->cost;
				plan->split_bin = split;
			}
		}
		++split;
	}
	return (best_cost);
}
