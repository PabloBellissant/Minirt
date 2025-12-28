/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cut_index.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 06:40:47 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/14 20:05:58 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "minirt.h"
#include "calc.h"

#define QUALIBRATION 2 

int	get_cut_index(t_vector *object_ptr, t_aabb_bvh *bvh, int axis)
{
	return ((object_ptr->num_elements) / 2);
	float		middle_value;
	float		actual_value;
	int			i;
	int			end;
	t_object	**object;

	object = (t_object **)object_ptr->data;
	middle_value = (bvh->max.data[axis] + bvh->min.data[axis]) / 2;
	i = imax(1, (int)(object_ptr->num_elements / 2) - QUALIBRATION);
	end = imin((int)(object_ptr->num_elements / 2) + QUALIBRATION,
			(int)object_ptr->num_elements - 1);
	while (i < end)
	{
		actual_value = get_center(object[i]).data[axis];
		if (actual_value >= middle_value)
			return (i);
		++i;
	}
	return ((object_ptr->num_elements + 1) / 2);
}
