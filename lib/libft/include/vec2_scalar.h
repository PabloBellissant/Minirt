/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_scalar.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:03:26 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/06 09:12:57 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2_SCALAR_H
# define VEC2_SCALAR_H

# include "vectors_types.h"

static inline t_vec2	vec2_scale(const t_vec2 v, const float s)
{
	return ((t_vec2){{{v.x * s, v.y * s}}});
}
static inline t_vec2	vec2_add_scalar(const t_vec2 v, const float s)
{
	return ((t_vec2){{{v.x + s, v.y + s}}});
}
static inline t_vec2	vec2_sub_scalar(const t_vec2 v, const float s)
{
	return ((t_vec2){{{v.x - s, v.y - s}}});
}
static inline t_vec2	vec2_div_scalar(const t_vec2 v, const float s)
{
	return ((t_vec2){{{v.x / s, v.y / s}}});
}

#endif