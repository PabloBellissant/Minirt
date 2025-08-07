/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4i_scalar.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:09:57 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/07 01:29:14 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC4I_SCALAR_H
# define VEC4I_SCALAR_H

# include "vectors_types.h"

static inline t_vec4i	vec4i_scale(const t_vec4i v, const int s)
{
	return ((t_vec4i){{{v.x * s, v.y * s, v.z * s, v.w * s}}});
}

static inline t_vec4i	vec4i_add_scalar(const t_vec4i v, const int s)
{
	return ((t_vec4i){{{v.x + s, v.y + s, v.z + s, v.w + s}}});
}

static inline t_vec4i	vec4i_sub_scalar(const t_vec4i v, const int s)
{
	return ((t_vec4i){{{v.x - s, v.y - s, v.z - s, v.w - s}}});
}

#endif