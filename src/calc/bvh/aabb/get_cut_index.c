/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cut_index.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 06:40:47 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/12 06:40:50 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "calc.h"

#define QUALIBRATION 2

int	get_cut_index(t_vector *object_ptr, t_aabb_bvh *bvh, int axis)
{
	float		middle_value;
	float		actual_value;
	int			i;
	int			end;
	t_object	**object;

	object = (t_object **)object_ptr->data;
	middle_value = (bvh->max.data[axis] + bvh->min.data[axis]) / 2;
	i = imax(0, (int)(object_ptr->num_elements / 2) - QUALIBRATION);
	end = imin((int)(object_ptr->num_elements / 2) + QUALIBRATION,
			(int)object_ptr->num_elements);
	while (i < end)
	{
		actual_value = get_center(object[i]).data[axis];
		if (actual_value >= middle_value)
			break ;
		++i;
	}
	if (i == 0)
		i = 1;
	else if (i == (int)object_ptr->num_elements)
		i = (int)object_ptr->num_elements - 1;
	return (i);
}
