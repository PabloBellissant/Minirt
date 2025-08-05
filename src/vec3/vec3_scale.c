/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_scale.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 05:29:12 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 05:04:26 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	*vec3_scale(t_vec3 *vec, float t);

inline t_vec3	*vec3_scale(t_vec3 *vec, const float t)
{
	vec->x *= t;
	vec->y *= t;
	vec->z *= t;
	return (vec);
}
