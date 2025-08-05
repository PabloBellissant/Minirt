/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_add_scalar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 05:31:47 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 05:02:35 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

t_vec3	*vec3_add_scalar(t_vec3 *vec, float x);

inline t_vec3	*vec3_add_scalar(t_vec3 *vec, const float x)
{
	vec->x += x;
	vec->y += x;
	vec->z += x;
	return (vec);
}
