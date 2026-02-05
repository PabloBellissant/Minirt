/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_axis_and_bin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:25:01 by jaubry--          #+#    #+#             */
/*   Updated: 2026/01/19 17:16:54 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_sah.h"

// 2) Prefix sums (left)
static inline void	prefix_sums_left(t_cuboid left_box[NUM_BINS], int left_count[NUM_BINS], t_bin bins[NUM_BINS])
{
	t_cuboid	acc_box;
	int			acc_count;
	int			b_idx;

	acc_box.min = vec3(SM, SM, SM);
	acc_box.max = vec3(-SM, -SM, -SM);
	acc_count = 0;
	b_idx = 0;
	while (b_idx < NUM_BINS)
	{
		if (bins[b_idx].count > 0)
		{
			if (acc_count == 0)
				acc_box = (t_cuboid){bins[b_idx].min, bins[b_idx].max};
			else
				eval_min_max((t_vec3 *[MM]){&acc_box.min, &acc_box.max},
						(t_vec3[MM]){acc_box.min, acc_box.max},
						(t_vec3[MM]){bins[b_idx].min, bins[b_idx].max});
		}
		acc_count += bins[b_idx].count;
		left_box[b_idx] = acc_box;
		left_count[b_idx] = acc_count;
		b_idx++;
	}
}

// 3) Suffix sums (right)
static inline void	suffix_sums_right(t_cuboid right_box[NUM_BINS], int right_count[NUM_BINS], t_bin bins[NUM_BINS])
{
	t_cuboid	acc_box;
	int			acc_count;
	int			b_idx;

	acc_box.min = vec3(SM, SM, SM);
	acc_box.max = vec3(-SM, -SM, -SM);
	acc_count = 0;
	b_idx = NUM_BINS - 1;
	while (b_idx >= 0)
	{
		if (bins[b_idx].count > 0)
		{
			if (acc_count == 0)
				acc_box = (t_cuboid){bins[b_idx].min, bins[b_idx].max};
			else
				eval_min_max((t_vec3 *[MM]){&acc_box.min, &acc_box.max},
						(t_vec3[MM]){acc_box.min, acc_box.max},
						(t_vec3[MM]){bins[b_idx].min, bins[b_idx].max});
		}
		acc_count += bins[b_idx].count;
		right_box[b_idx] = acc_box;
		right_count[b_idx] = acc_count;
		b_idx--;
	}
}

/*
	Computation based on partition area, left and right area, and count of object in left and right
*/
static inline float	sah_cost(float sa_p, float sa[SPLIT], int n[SPLIT])
{
	if (sa_p <= 0.0f)
		return (SM);
	return (CT + CI * ((sa[LEFT] / sa_p * n[LEFT]) + (sa[RIGHT] / sa_p * n[RIGHT])));
}

// 4) Evaluate SAH at each split
static inline void	evaluate_sah(int axis, t_cuboid box[SPLIT][NUM_BINS], int count[SPLIT][NUM_BINS], int *out_axis, int *out_bin, t_aabb_bvh *parent_bvh, float *best_cost)
{
	const float	sa_p = get_cuboid_area(&parent_bvh->cuboid);
	float		sa[SPLIT];
	float		cost;
	int			b_idx;

	b_idx = 0;
	while (b_idx < (NUM_BINS - 1))
	{
		if ((count[LEFT][b_idx] > 0) && (count[RIGHT][b_idx + 1] > 0))
		{
			sa[LEFT] = get_cuboid_area(&box[LEFT][b_idx]);
			sa[RIGHT] = get_cuboid_area(&box[RIGHT][b_idx + 1]);
			cost = sah_cost(sa_p, sa, (int[SPLIT]){count[LEFT][b_idx], count[RIGHT][b_idx + 1]});
			if (cost < *best_cost)
			{
				*best_cost = cost;
				*out_axis = axis;
				*out_bin = b_idx;
			}
		}
		b_idx++;
	}
}

void	get_axis_and_bin(int axis, int *out_axis, int *out_bin, t_bin bins[NUM_BINS], t_aabb_bvh *parent_bvh, float *best_cost)
{
	t_cuboid	box[SPLIT][NUM_BINS];
	int			count[SPLIT][NUM_BINS];

	prefix_sums_left(box[LEFT], count[LEFT], bins);
	suffix_sums_right(box[RIGHT], count[RIGHT], bins);
	evaluate_sah(axis, box, count, out_axis, out_bin, parent_bvh, best_cost);
}
