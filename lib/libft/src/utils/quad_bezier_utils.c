/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quad_bezier_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:27:40 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/07 09:30:46 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"
#include <math.h>
#include <stdlib.h>

#define CURVE_RESOLUTION	4.0f
#define MIN_CURVE_RES		0.01f
#define MAX_CURVE_RES		0.99f

/*
	Euclidean distance, achieving approximately 3.5% error rate.
*/
static inline int	fast_distance(const t_vec2i a, const t_vec2i b)
{
	const int	dx = abs(b.x - a.x);
	const int	dy = abs(b.y - a.y);
	int			min_val;

	if (dx < dy)
		min_val = dx;
	else
		min_val = dy;
	return (dx + dy - (min_val >> 1) - (min_val >> 2) + (min_val >> 4));
}

/*
	Function that returns the coordinates of a point based on the quadratic
	bezier curves coordinates of start, end and control point and uses
	t to travel from start to end.
*/
t_vec2i	quad_bezier_pt(const t_vec2i start, const t_vec2i ctrl,
			const t_vec2i end, const float t)
{
	const float	m = (1 - t);
	const float	a = m * m;
	const float	b = 2 * m * t;
	const float	c = t * t;

	return (vec2i(((a * start.x) + (b * ctrl.x) + (c * end.x)),
			((a * start.y) + (b * ctrl.y) + (c * end.y))));
}

static inline float	clamp(const float value, const float min_val,
						const float max_val)
{
	return (fmaxf(min_val, fminf(value, max_val)));
}

/*
	Function to get the ideal resolution for a bezier curve for the
	minimal number of subdivision but with the best look for each possible
	curves.
*/
float	quad_bezier_res(const t_vec2i start, const t_vec2i ctrl,
			const t_vec2i end)
{
	const float	a = fast_distance(start, ctrl);
	const float	b = fast_distance(ctrl, end);
	const float	c = fast_distance(start, end);

	if (((a + b) == 0) || (c == 0))
		return (-1);
	return (clamp(((a + b) / c) / CURVE_RESOLUTION,
			MIN_CURVE_RES, MAX_CURVE_RES));
}

float	quad_curve_length(const t_vec2i start, const t_vec2i ctrl,
			const t_vec2i end)
{
	const float	chord_length = fast_distance(start, end);
	const float	ctrl_length = fast_distance(start, ctrl)
		+ fast_distance(ctrl, end);

	return ((chord_length + ctrl_length) * 0.5f);
}
