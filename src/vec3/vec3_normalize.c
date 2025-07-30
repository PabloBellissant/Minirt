/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 06:43:43 by jaubry--          #+#    #+#             */
/*   Updated: 2025/07/30 05:48:40 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

/*
	Function that computes the normalized version of a direction vector
*/
t_vec3	*vec3_normalize(t_vec3 *vec)
{
	return (vec3_div_scalar(vec, vec3_magnitude(vec)));
}