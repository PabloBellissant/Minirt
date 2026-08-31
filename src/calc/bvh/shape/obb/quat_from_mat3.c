/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_from_mat3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:55:26 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/02 23:59:12 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec4_constructors.h"
#include "bvh.h"

static inline t_vec4	quat_from_trace(t_mat3 m, float trace)
{
	float	s;

	s = sqrtf(trace + 1.0f) * 2.0f;
	return (vec4(
			(m.m[2][1] - m.m[1][2]) / s,
			(m.m[0][2] - m.m[2][0]) / s,
			(m.m[1][0] - m.m[0][1]) / s,
			0.25f * s
		));
}

static inline t_vec4	quat_from_diag(t_mat3 m, int i)
{
	float	s;

	if (i == 0)
	{
		s = sqrtf(1.0f + m.m[0][0] - m.m[1][1] - m.m[2][2]) * 2.0f;
		return (vec4(0.25f * s, (m.m[0][1] + m.m[1][0]) / s,
				(m.m[0][2] + m.m[2][0]) / s, (m.m[2][1] - m.m[1][2]) / s));
	}
	else if (i == 1)
	{
		s = sqrtf(1.0f + m.m[1][1] - m.m[0][0] - m.m[2][2]) * 2.0f;
		return (vec4((m.m[0][1] + m.m[1][0]) / s, 0.25f * s,
				(m.m[1][2] + m.m[2][1]) / s, (m.m[0][2] - m.m[2][0]) / s));
	}
	s = sqrtf(1.0f + m.m[2][2] - m.m[0][0] - m.m[1][1]) * 2.0f;
	return (vec4((m.m[0][2] + m.m[2][0]) / s, (m.m[1][2] + m.m[2][1]) / s,
			0.25f * s, (m.m[1][0] - m.m[0][1]) / s));
}

t_vec4	quat_from_mat3_cols(t_mat3 m)
{
	float	trace;
	t_vec4	q;
	int		i;

	trace = m.m[0][0] + m.m[1][1] + m.m[2][2];
	if (trace > 0.0f)
		q = quat_from_trace(m, trace);
	else
	{
		i = 0;
		if (m.m[1][1] > m.m[0][0])
			i = 1;
		if (m.m[2][2] > m.m[i][i])
			i = 2;
		q = quat_from_diag(m, i);
	}
	return (quat_normalize_safe(q));
}
