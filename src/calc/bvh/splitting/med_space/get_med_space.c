/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_med_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 01:52:06 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/04 23:38:19 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

static inline float	get_mean_value(const t_bvh_header *bvh_header,
						const t_bvh_bounds parent_bounds,
						const t_vector primitives, const t_axis axis)
{
	const t_object	*first = (t_object *)get_vector_value(&primitives, 0);
	const t_object	*last = (t_object *)get_last_vector_value(&primitives);

	return ((key_obj(bvh_header->shape, parent_bounds, *first, axis)
			+ key_obj(bvh_header->shape, parent_bounds, *last, axis)) / 2.0f);
}

size_t	get_med_space(const t_bvh_header *bvh_header,
			const t_bvh_bounds parent_bounds, const t_vector primitives)
{
	const t_axis	axis = get_axis_split(bvh_header, parent_bounds,
			primitives);
	const t_object	*objects = primitives.data;
	size_t			left_count;
	float			mean_val;

	sort_prim(bvh_header, parent_bounds, primitives, axis);
	mean_val = get_mean_value(bvh_header, parent_bounds, primitives, axis);
	left_count = 0;
	while ((left_count < primitives.num_elements)
		&& (mean_val > key_obj(bvh_header->shape, parent_bounds,
				objects[left_count], axis)))
		left_count++;
	return (left_count);
}
