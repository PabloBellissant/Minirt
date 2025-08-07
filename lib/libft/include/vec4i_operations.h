/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec4i_operations.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:02:49 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/07 01:39:54 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC4I_OPERATIONS_H
# define VEC4I_OPERATIONS_H

# include "vectors_types.h"

static inline t_vec4i	vec4i(const int x, const int y, const int z,
							const int w)
{
	return ((t_vec4i){{{x, y, z, w}}});
}

static inline t_vec4i	vec4i_add(const t_vec4i a, const t_vec4i b)
{
	return ((t_vec4i){{{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w}}});
}

static inline t_vec4i	vec4i_sub(const t_vec4i a, const t_vec4i b)
{
	return ((t_vec4i){{{a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w}}});
}

static inline t_vec4i	vec4i_mult(const t_vec4i a, const t_vec4i b)
{
	return ((t_vec4i){{{a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w}}});
}

#endif