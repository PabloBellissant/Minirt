/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sphere_bvh.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 05:16:07 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/12 05:16:10 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bvh.h"

void	merge_sphere_bvh(t_vector *bvh_vec, size_t a_index, size_t b_index)
{
	t_sphere_bvh	bvh;
	t_sphere_bvh	*a;
	t_sphere_bvh	*b;
	t_vec3			dir;

	a = get_vector_value(bvh_vec, a_index);
	b = get_vector_value(bvh_vec, b_index);
	bvh.depth = fmaxf(a->depth, b->depth) + 1;
	bvh.next_a = a;
	bvh.next_b = b;
	dir = vec3_sub(b->pos, a->pos);
	bvh.size = (vec3_length(dir) + a->size + b->size) / 2.0f;
	bvh.pos = vec3_add(a->pos, vec3_scale(vec3_normalize(dir), bvh.size - a->size));
	vector_add(bvh_vec, &bvh, 1);
}
