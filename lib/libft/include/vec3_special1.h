/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_special1.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 08:07:39 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/07 01:41:10 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_SPECIAL1_H
# define VEC3_SPECIAL1_H

# include "vectors_types.h"
# include "vec3_scalar.h"
# include <math.h>

static inline float	vec3_dot(const t_vec3 a, const t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/*
	Cross product optimized for direct register computation
	No temporary variables for maximum performance
*/
static inline t_vec3	vec3_cross(const t_vec3 a, const t_vec3 b)
{
	return ((t_vec3){{{
				a.y * b.z - a.z * b.y,
				a.z * b.x - a.x * b.z,
				a.x * b.y - a.y * b.x
			}}});
}

static inline float	vec3_length2(const t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

//magnitude
//	return (sqrt(vec3_length_squared(v)));

//unit
// return (vec3_div_scalar(v, vec3_length(v)))

//normalize
// return (vec3_div_scalar(v, vec3_magnitude(v)));

/*
	Same as vec3_magnitude
*/
static inline float	vec3_length(const t_vec3 v)
{
	return (sqrtf(vec3_length2(v)));
}

static inline t_vec3	vec3_lerp(const t_vec3 a, const t_vec3 b, const float t)
{
	return ((t_vec3){{{
				a.x * (1.0f - t) + b.x * t,
				a.y * (1.0f - t) + b.y * t,
				a.z * (1.0f - t) + b.z * t
			}}});
}

/*
static inline t_vec3	fast_vec3_lerp(const t_vec3 a, const t_vec3 b, float t)
{
	return ((t_vec3){{{
		fmaf(t, b.x - a.x, a.x),
		fmaf(t, b.y - a.y, a.y),
		fmaf(t, b.z - a.z, a.z)
	}}});
}
*/

#endif