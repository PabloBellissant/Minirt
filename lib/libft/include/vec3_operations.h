/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_operations.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:00:24 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/06 09:12:57 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_OPERATIONS_H
# define VEC3_OPERATIONS_H

# include "vectors_types.h"

static inline t_vec3	vec3(const float x, const float y, const float z)
{
	return ((t_vec3){{{x, y, z}}});
}
static inline t_vec3	vec3_add(const t_vec3 a, const t_vec3 b)
{
	return ((t_vec3){{{a.x + b.x, a.y + b.y, a.z + b.z}}});
}
static inline t_vec3	vec3_sub(const t_vec3 a, const t_vec3 b)
{
	return ((t_vec3){{{a.x - b.x, a.y - b.y, a.z - b.z}}});
}
static inline t_vec3	vec3_mult(const t_vec3 a, const t_vec3 b)
{
	return ((t_vec3){{{a.x * b.x, a.y * b.y, a.z * b.z}}});
}

#endif