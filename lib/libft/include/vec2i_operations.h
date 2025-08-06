/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2i_operations.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 07:59:17 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/06 09:13:01 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2I_OPERATIONS_H
# define VEC2I_OPERATIONS_H

# include "vectors_types.h"

static inline t_vec2i	vec2i(const int x, const int y)
{
	return ((t_vec2i){{{x, y}}});
}
static inline t_vec2i	vec2i_add(const t_vec2i a, const t_vec2i b)
{
	return ((t_vec2i){{{a.x + b.x, a.y + b.y}}});
}
static inline t_vec2i	vec2i_sub(const t_vec2i a, const t_vec2i b)
{
	return ((t_vec2i){{{a.x - b.x, a.y - b.y}}});
}
static inline t_vec2i	vec2i_mult(const t_vec2i a, const t_vec2i b)
{
	return ((t_vec2i){{{a.x * b.x, a.y * b.y}}});
}

#endif