/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_scalar.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:07:14 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/06 09:12:57 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_SCALAR_H
# define VEC3_SCALAR_H

# include "vectors_types.h"

static inline t_vec3	vec3_scale(const t_vec3 v, const float s)
{
	return ((t_vec3){{{v.x * s, v.y * s, v.z * s}}});
}
static inline t_vec3	vec3_add_scalar(const t_vec3 v, const float s)
{
	return ((t_vec3){{{v.x + s, v.y + s, v.z + s}}});
}
static inline t_vec3	vec3_sub_scalar(const t_vec3 v, const float s)
{
	return ((t_vec3){{{v.x - s, v.y - s, v.z - s}}});
}
static inline t_vec3	vec3_div_scalar(const t_vec3 v, const float s)
{
	return ((t_vec3){{{v.x / s, v.y / s, v.z / s}}});
}

#endif