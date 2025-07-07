/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_bvh_area.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 03:15:55 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/01 03:15:56 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "bvh.h"

float	get_next_bvh_area(t_bvh *a, t_bvh *b)
{
	float	area;
	t_vec3	base_pos;
	t_vec3	size;

	base_pos.x = ft_minf(a->pos.x, b->pos.x);
	base_pos.y = ft_minf(a->pos.y, b->pos.y);
	base_pos.z = ft_minf(a->pos.z, b->pos.z);
	size.x = ft_maxf(a->pos.x + a->size.x, b->pos.x + b->size.x) - base_pos.x;
	size.y = ft_maxf(a->pos.y + a->size.y, b->pos.y + b->size.y) - base_pos.y;
	size.z = ft_maxf(a->pos.z + a->size.z, b->pos.z + b->size.z) - base_pos.z;
	area = size.x * size.y;
	area += size.y * size.z;
	area += size.x * size.z;
	return (area * 2);
}
