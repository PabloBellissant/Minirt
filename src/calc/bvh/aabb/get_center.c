/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_center.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 06:36:42 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/12 06:36:45 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	get_center(const t_object *o)
{
	t_vec3	min;

	if (o->type == TRIANGLE)
	{
		min = vec3_add(o->triangle.p0.pos, o->triangle.p1.pos);
		min = vec3_add(min, o->triangle.p2.pos);
		min = vec3_div_scalar(min, 3);
	}
	if (o->type == SPHERE)
	{
		return (o->sphere.pos);
	}
	if (o->type == CYLINDER)
	{
		return (vec3_add(o->cylinder.pos, vec3_scale(o->cylinder.rot, 0.5f)));
	}
	return (min);
}
