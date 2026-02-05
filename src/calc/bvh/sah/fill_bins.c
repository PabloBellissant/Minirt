/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_bins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 14:25:52 by jaubry--          #+#    #+#             */
/*   Updated: 2026/01/19 15:01:18 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_sah.h"
#include "object.h"

static inline void	fill_bin(int b_idx, t_object *obj_out, t_bin bins[NUM_BINS])
{
	t_vec3	obj_min;
	t_vec3	obj_max;

	if (b_idx < 0)
		b_idx = 0;
	if (b_idx >= NUM_BINS)
		b_idx = NUM_BINS - 1;

	get_min_max(obj_out, &obj_min, &obj_max);
	if (bins[b_idx].count == 0)
	{
		bins[b_idx].min = obj_min;
		bins[b_idx].max = obj_max;
	}
	else
		eval_min_max((t_vec3 *[MM]){&(bins[b_idx].min), &(bins[b_idx].max)},
				(t_vec3[MM]){bins[b_idx].min, bins[b_idx].max}, (t_vec3[MM]){obj_min, obj_max});
	bins[b_idx].count++;
}

// 1) Fill bins
void fill_bins(int axis, t_vec3 cmin, float inv_extent, t_vector *index_vec, t_object *objects, t_bin bins[NUM_BINS])
{
	t_vec2i	*indices;
	int		b_idx;
	t_vec3	c;
	size_t	i;

	indices = (t_vec2i *)index_vec->data;
	i = 0;
	while (i < index_vec->num_elements)
	{
		c = get_bin_centroid(objects, indices[i].x);
		b_idx = (int)(((&c.x)[axis] - (&cmin.x)[axis]) * inv_extent);
		fill_bin(b_idx, &objects[indices[i].x], bins);
		i++;
	}
}
