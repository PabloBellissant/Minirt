/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:34:43 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/22 22:47:33 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct.h"
#include "draw.h"

static void	bresenham_h(t_data *data, t_vec2i p1, t_vec2i p2, int color);
static void	bresenham_v(t_data *data, t_vec2i p1, t_vec2i p2, int color);

void	draw_line(t_data *data, t_vec2i point_a, t_vec2i point_b)
{
	if (abs(point_b.y - point_a.y)
		<= abs(point_b.x - point_a.x))
	{
		if (point_b.x < point_a.x)
			bresenham_h(data, point_b, point_a, 0xFFFFFF);
		else
			bresenham_h(data, point_a, point_b, 0xFFFFFF);
	}
	else
	{
		if (point_b.y < point_a.y)
			bresenham_v(data, point_b, point_a, 0xFFFFFF);
		else
			bresenham_v(data, point_a, point_b, 0xFFFFFF);
	}
}

static void	bresenham_h(t_data *data, t_vec2i p1, t_vec2i p2, int color)
{
	int	dx;
	int	dy;
	int	dir;
	int	err;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	dir = 1;
	if (dy < 0)
		dir = -1;
	dy *= dir;
	err = 2 * dy - dx;
	while (p1.x <= p2.x)
	{
		++p1.x;
		safe_put_pixel(data->addr, p1.x, p1.y, color);
		if (err >= 0)
		{
			p1.y += dir;
			err -= 2 * dx;
		}
		err += 2 * dy;
	}
}

static void	bresenham_v(t_data *data, t_vec2i p1, t_vec2i p2, int color)
{
	int	dx;
	int	dy;
	int	dir;
	int	err;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	dir = 1;
	if (dx < 0)
		dir = -1;
	dx *= dir;
	err = 2 * dx - dy;
	while (p1.y <= p2.y)
	{
		++p1.y;
		safe_put_pixel(data->addr, p1.x, p1.y, color);
		if (err >= 0)
		{
			p1.x += dir;
			err -= 2 * dy;
		}
		err += 2 * dx;
	}
}
