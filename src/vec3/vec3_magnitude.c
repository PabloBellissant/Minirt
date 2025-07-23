/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_magnitude.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 06:45:54 by jaubry--          #+#    #+#             */
/*   Updated: 2025/07/23 06:51:44 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include <math.h>

/*
	Function that computes the magnitude of a direction vector
*/
float	vec3_magnitude(const t_vec3 *v)
{
	return (sqrt(vec3_length_squared(v)));
}