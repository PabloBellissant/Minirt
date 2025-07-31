/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 04:28:42 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/31 20:29:37 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include "struct.h"

t_vec3	*vec3_add(const t_vec3 *vec1, const t_vec3 *vec2, t_vec3 *out);
t_vec3	*vec3_sub(const t_vec3 *vec1, const t_vec3 *vec2, t_vec3 *out);
t_vec3	*vec3_scale(t_vec3 *vec1, const float x);
t_vec3	*vec3_add_scalar(t_vec3 *vec, const float x);
t_vec3	*vec3_div_scalar(t_vec3 *vec, const float x);

float	vec3_length(const t_vec3 *v);
float	vec3_length_squared(const t_vec3 *v);
float	*vec3_dot(const t_vec3 *u, const t_vec3 *v, float *result);
t_vec3	*vec3_unit(t_vec3 *v);
t_vec3	*vec3_lerp(t_vec3 *a, t_vec3 *b, float t, t_vec3 *result);
t_vec3	*vec3_cross(t_vec3 *a, t_vec3 *b, t_vec3 *out);

t_vec3	*vec3_random(t_vec3 *vec);

t_vec3	*vec3_normalize(t_vec3 *vec);
float	vec3_magnitude(const t_vec3 *v);
t_vec3	*vec3_mult(const t_vec3 *vec1, const t_vec3 *vec2, t_vec3 *out);

#endif
