/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_prim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 00:22:27 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/05 03:36:10 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

static inline void	swap_obj(t_object *a, t_object *b)
{
	const t_object	tmp = *a;

	*a = *b;
	*b = tmp;
}

static inline void	sift_down(const t_sort_params *p, size_t n, size_t root)
{
	size_t	child;
	size_t	swap_i;

	while ((root * BVH_ARITY + 1) < n)
	{
		child = root * BVH_ARITY + 1;
		swap_i = root;
		if (key_obj(p->shape, p->bounds, p->a[swap_i], p->axis)
			< key_obj(p->shape, p->bounds, p->a[child], p->axis))
			swap_i = child;
		if (((child + 1) < n)
			&& (key_obj(p->shape, p->bounds, p->a[swap_i], p->axis)
				< key_obj(p->shape, p->bounds, p->a[child + 1], p->axis)))
			swap_i = child + 1;
		if (swap_i == root)
			return ;
		swap_obj(&p->a[root], &p->a[swap_i]);
		root = swap_i;
	}
}

void	sort_prim(const t_bvh_header *bvh_header,
			const t_bvh_bounds parent_bounds, t_vector primitives,
			const t_axis axis)
{
	size_t				i;
	size_t				end;
	const t_sort_params	p = (t_sort_params)
	{
		.shape = bvh_header->shape,
		.bounds = parent_bounds,
		.axis = axis,
		.a = primitives.data,
		.n = primitives.num_elements
	};

	if (p.a && (p.n < BVH_ARITY))
		return ;
	i = p.n / 2;
	while (i > 0)
		sift_down(&p, p.n, --i);
	end = p.n;
	while (end > 1)
	{
		--end;
		swap_obj(&p.a[0], &p.a[end]);
		sift_down(&p, end, 0);
	}
}
