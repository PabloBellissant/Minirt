/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_div_scalar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 05:31:47 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/30 05:49:22 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

t_vec3	*vec3_div_scalar(t_vec3 *vec, float x);

inline t_vec3	*vec3_div_scalar(t_vec3 *vec, const float x)
{
	vec->x /= x;
	vec->y /= x;
	vec->z /= x;
	return (vec);
}
