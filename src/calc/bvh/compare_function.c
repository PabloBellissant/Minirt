/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 05:10:53 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/12 05:10:55 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	get_center(const t_object *o);

int	compare_x(const void *a, const void *b)
{
	const t_object *const	*obj_a = a;
	const t_object *const	*obj_b = b;

	if (get_center(*obj_a).x < get_center(*obj_b).x)
		return (-1);
	return (1);
}

int	compare_y(const void *a, const void *b)
{
	const t_object *const	*obj_a = a;
	const t_object *const	*obj_b = b;

	if (get_center(*obj_a).y < get_center(*obj_b).y)
		return (-1);
	return (1);
}

int	compare_z(const void *a, const void *b)
{
	const t_object *const	*obj_a = a;
	const t_object *const	*obj_b = b;

	if (get_center(*obj_a).z < get_center(*obj_b).z)
		return (-1);
	return (1);
}

int compare_dumb(const void *a, const void *b)
{
	const int *const *aa = a;
	const int *const *bb = b;

	if (*aa > *bb)
		return (-1);
	return (1);
}

int	(*get_axis_function(const int axis))(const void *a, const void *b)
{
	return (compare_dumb);
	if (axis == 0)
		return (compare_x);
	if (axis == 1)
		return (compare_y);
	return (compare_z);
}
