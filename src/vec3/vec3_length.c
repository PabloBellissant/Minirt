/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_length.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 06:37:13 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 05:03:34 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec3.h"

inline float	vec3_length(const t_vec3 *v)
{
	return (sqrtf(vec3_length_squared(v)));
}
