/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_lerp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 03:37:56 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/21 03:37:58 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

inline t_vec3*	vec3_lerp(t_vec3 *a, t_vec3 *b, float t, t_vec3 *result)
{
	result->x = (1 - t) * a->x + t * b->x;
	result->y = (1 - t) * a->y + t * b->y;
	result->z = (1 - t) * a->z + t * b->z;
	return (result);
}
