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
	t_bvh	bvh;
	t_bvh	*a;
	t_bvh	*b;

	a = get_vector_value(bvh_vec, a_index);
	b = get_vector_value(bvh_vec, b_index);
	bvh.depth = fmax(a->depth, b->depth) + 1;
	bvh.next_a = a;
	bvh.next_b = b;
	bvh.pos.x = fminf(a->pos.x, b->pos.x);
	bvh.pos.y = fminf(a->pos.y, b->pos.y);
	bvh.pos.z = fminf(a->pos.z, b->pos.z);
	bvh.size.x = fmaxf(a->pos.x + a->size.x - bvh.pos.x,
			b->pos.x + b->size.x - bvh.pos.x);
	bvh.size.y = fmaxf(a->pos.y + a->size.y - bvh.pos.y,
			b->pos.y + b->size.y - bvh.pos.y);
	bvh.size.z = fmaxf(a->pos.z + a->size.z - bvh.pos.z,
			b->pos.z + b->size.z - bvh.pos.z);
	bvh.parent = NULL;
	vector_add(bvh_vec, &bvh, 1);
	a = get_vector_value(bvh_vec, a_index);
	b = get_vector_value(bvh_vec, b_index);
	a->parent = get_vector_value(bvh_vec, bvh_vec->num_elements - 1);
	b->parent = a->parent;
}
