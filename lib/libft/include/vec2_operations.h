/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_operations.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 07:51:38 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/07 01:28:29 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2_OPERATIONS_H
# define VEC2_OPERATIONS_H

# include "vectors_types.h"

static inline t_vec2	vec2(const float x, const float y)
{
	return ((t_vec2){{x, y}});
}

static inline t_vec2	vec2_add(const t_vec2 a, const t_vec2 b)
{
	return ((t_vec2){{a.x + b.x, a.y + b.y}});
}

static inline t_vec2	vec2_sub(const t_vec2 a, const t_vec2 b)
{
	return ((t_vec2){{a.x - b.x, a.y - b.y}});
}

static inline t_vec2	vec2_mult(const t_vec2 a, const t_vec2 b)
{
	return ((t_vec2){{a.x * b.x, a.y * b.y}});
}

#endif