/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_quadratic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 01:54:59 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/13 01:55:02 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "calc.h"

int	solve_quadratic(t_quadratic *q)
{
	float	sqrt_delta;
	float	denom;

	q->delta = q->b * q->b - 4.0f * q->a * q->c;
	if (q->delta < 0.0f)
		return (0);
	denom = 2.0f * q->a;
	sqrt_delta = sqrtf(q->delta);
	q->t_min = (-q->b - sqrt_delta) / denom;
	q->t_max = (-q->b + sqrt_delta) / denom;
	return (q->t_min > 0 || q->t_max > 0);
}
