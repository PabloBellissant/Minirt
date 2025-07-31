/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 01:57:20 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/31 20:56:40 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "bvh.h"

int	get_object_count(t_bvh *bvh)
{
	int	object_count;

	if (bvh->depth == 0)
	{
		if ((bvh->object->type == PLANE) || (bvh->object->type == LIGHT))
			return (0);
		return (1);
	}
	object_count = get_object_count(bvh->next_a);
	object_count += get_object_count(bvh->next_b);
	return (object_count);
}
