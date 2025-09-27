/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_bvh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 02:43:30 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 05:13:30 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include <math.h>

void	merge_bvh(t_vector *bvh_vec, size_t a_index, size_t b_index)
{
	t_aabb_bvh	bvh;
	t_aabb_bvh	*a;
	t_aabb_bvh	*b;
	t_vec3		size;

	a = get_vector_value(bvh_vec, a_index);
	b = get_vector_value(bvh_vec, b_index);
	bvh.depth = fmaxf(a->depth, b->depth) + 1;
	bvh.next_a = a;
	bvh.next_b = b;
	bvh.min.x = fminf(a->min.x, b->min.x);
	bvh.min.y = fminf(a->min.y, b->min.y);
	bvh.min.z = fminf(a->min.z, b->min.z);
	size.x = fmaxf(a->max.x - bvh.min.x, b->max.x - bvh.min.x);
	size.y = fmaxf(a->max.y - bvh.min.y, b->max.y - bvh.min.y);
	size.z = fmaxf(a->max.z - bvh.min.z, b->max.z - bvh.min.z);
	bvh.max.x = bvh.min.x + size.x;
	bvh.max.y = bvh.min.y + size.y;
	bvh.max.z = bvh.min.z + size.z;
	vector_add(bvh_vec, &bvh, 1);
}
