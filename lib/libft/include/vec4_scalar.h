/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4_scalar.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:09:41 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/07 01:29:05 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC4_SCALAR_H
# define VEC4_SCALAR_H

# include "vectors_types.h"

static inline t_vec4	vec4_scale(const t_vec4 v, const float s)
{
	return ((t_vec4){{v.x * s, v.y * s, v.z * s, v.w * s}});
}

static inline t_vec4	vec4_add_scalar(const t_vec4 v, const float s)
{
	return ((t_vec4){{v.x + s, v.y + s, v.z + s, v.w + s}});
}

static inline t_vec4	vec4_sub_scalar(const t_vec4 v, const float s)
{
	return ((t_vec4){{v.x - s, v.y - s, v.z - s, v.w - s}});
}

static inline t_vec4	vec4_div_scalar(const t_vec4 v, const float s)
{
	return ((t_vec4){{v.x / s, v.y / s, v.z / s, v.w / s}});
}
#endif