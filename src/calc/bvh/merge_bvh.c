/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_bvh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 02:43:30 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/22 22:50:43 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "bvh.h"
#include <math.h>

int	merge_bvh(t_vector *bvh_vec, t_bvh *a, t_bvh *b)
{
	t_bvh	bvh;

	bvh.depth = fmax(a->depth, b->depth);
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
	if (vector_add(bvh_vec, &bvh, 1) == -1)
		return (-1);
	a->parent = get_vector_value(bvh_vec, bvh_vec->num_elements - 1);
	b->parent = a->parent;
	return (0);
}
