/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_bound.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 01:21:49 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/27 01:21:52 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors_types.h"
#include "bvh.h"
#include "calc.h"

int	apply_bound(t_vec2i *proj, t_bound *bound)
{
	if (proj->x == -1)
	{
		bound->top = 0;
		bound->down = HEIGHT - 1;
		bound->left = 0;
		bound->right = WIDTH - 1;
		return (-1);
	}
	if (proj->y < bound->top)
		bound->top = imax(proj->y, 0);
	if (proj->y > bound->down)
		bound->down = imin(proj->y, HEIGHT - 1);
	if (proj->x < bound->left)
		bound->left = imax(proj->x, 0);
	if (proj->x > bound->right)
		bound->right = imin(proj->x, WIDTH - 1);
	return (0);
}
