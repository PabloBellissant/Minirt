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

	a = get_vector_value(bvh_vec, a_index);
	b = get_vector_value(bvh_vec, b_index);
	bvh.depth = fmaxf(a->depth, b->depth) + 1;
	bvh.next_a = a;
	bvh.next_b = b;
	t_vec3 dir = vec3_sub(b->pos, a->pos);
	float dist = vec3_length(dir);

	// Handle full containment cases
	if (a->size >= dist + b->size) {
		bvh.pos = a->pos;
		bvh.size = a->size;
	} else if (b->size >= dist + a->size) {
		bvh.pos = b->pos;
		bvh.size = b->size;
	} else {
		t_vec3 norm_dir = vec3_div_scalar(dir, dist);
		bvh.size = (dist + a->size + b->size) / 2.0f;
		bvh.pos = vec3_add(a->pos, vec3_scale(norm_dir, bvh.size - a->size));
	}
	vector_add(bvh_vec, &bvh, 1);
}
