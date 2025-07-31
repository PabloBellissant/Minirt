/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:01:32 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/31 20:22:46 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "define.h"
#include "mlx.h"
#include "struct.h"

void	disable_decorations(Display *d, Window w)
{
	MotifWmHints	hints;
	Atom			prop;

	hints.flags = (1L << 1);//find define
	hints.decorations = 0;
	prop = XInternAtom(d, "_MOTIF_WM_HINTS", False);
	XChangeProperty(d, w, prop, prop, 32, PropModeReplace,
		(unsigned char *)&hints, 5);
}

int	mlx_ext_fullscreen(t_xvar *xvar, t_win_list *win, int fullscreen);

int	init_img(t_data *data)
{
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->img == NULL)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		return (-1);
	}
	data->addr = (int *)mlx_get_data_addr(data->img, &data->bits,
			&data->line_len, &data->endian);
	return (0);
}

int	init_graphics(t_data *data)
{
	data->screen.x = WIDTH;
	data->screen.y = HEIGHT;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (-1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, TITLE);
	if (!data->win)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		return (-1);
	}
	if (WINDOWLESS || FULLSCREEN)
		disable_decorations(data->mlx->display, data->win->window);
	if (FULLSCREEN)
		mlx_ext_fullscreen(data->mlx, data->win, 1);
	return (init_img(data));
}
