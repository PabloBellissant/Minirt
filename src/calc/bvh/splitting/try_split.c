/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 23:38:44 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 12:23:37 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

int	try_split(t_vector primitives, t_vector child_prim[BVH_LR],
		size_t left_count, size_t right_count)
{
	vector_init(&child_prim[BVH_L], sizeof(t_object));
	if (vector_add(&child_prim[BVH_L], primitives.data, left_count) != 0)
	{
		free_vector(&primitives);
		return (-1);
	}
	vector_init(&child_prim[BVH_R], sizeof(t_object));
	if (vector_add(&child_prim[BVH_R],
			get_vector_value(&primitives, left_count), right_count) != 0)
	{
		free_vector(&child_prim[BVH_L]);
		free_vector(&primitives);
		return (-1);
	}
	free_vector(&primitives);
	return (0);
}
