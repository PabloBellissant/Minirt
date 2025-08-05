/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_cross.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 07:27:56 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 05:03:14 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	*vec3_cross(t_vec3 *a, t_vec3 *b, t_vec3 *out);

inline t_vec3	*vec3_cross(t_vec3 *a, t_vec3 *b, t_vec3 *out)
{
	t_vec3	temp;

	temp.x = a->y * b->z - a->z * b->y;
	temp.y = a->z * b->x - a->x * b->z;
	temp.z = a->x * b->y - a->y * b->x;
	*out = temp;
	return (out);
}
