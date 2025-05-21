/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:01:32 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/21 02:01:34 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "string.h"
#include "mlx.h"
#include "struct.h"

int	init_graphics(t_data *data)
{
	t_screen	screen;

	data->screen.dim_x = 1920;
	data->screen.dim_y = 1080;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (-1);
	screen = data->screen;
	data->win = mlx_new_window(data->mlx, screen.dim_x, screen.dim_y, TITLE);
	if (!data->win)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		return (-1);
	}
	data->img = mlx_new_image(data->mlx, screen.dim_x, screen.dim_y);
	if (data->img == NULL)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		return (-1);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bits, &data->line_len, &data->endian);
	return (0);
}
