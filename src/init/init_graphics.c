/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:01:32 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/30 18:44:53 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "define.h"
#include "mlx.h"
#include "struct.h"

typedef struct {
	unsigned long flags;
	unsigned long functions;
	unsigned long decorations;
	long input_mode;
	unsigned long status;
} MotifWmHints;

void	disable_decorations(Display *d, Window w)
{
	MotifWmHints hints;
	Atom prop;

	hints.flags = (1L << 1);
	hints.decorations = 0;

	prop = XInternAtom(d, "_MOTIF_WM_HINTS", False);
	XChangeProperty(d, w, prop, prop, 32, PropModeReplace, (unsigned char *)&hints, 5);
}

int	mlx_ext_fullscreen(t_xvar *xvar, t_win_list *win, int fullscreen);

int	init_graphics(t_data *data)
{
	t_vec2i	screen;

	data->screen.x = WIDTH;
	data->screen.y = HEIGHT;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (-1);
	screen = data->screen;
	data->win = mlx_new_window(data->mlx, screen.x, screen.y, TITLE);
	if (!data->win)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		return (-1);
	}
	//disable_decorations(data->mlx->display, data->win->window);
	//mlx_ext_fullscreen(data->mlx, data->win, 1);
	data->img = mlx_new_image(data->mlx, screen.x, screen.y);
	if (data->img == NULL)
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		return (-1);
	}
	data->addr = (int *)mlx_get_data_addr(data->img, &data->bits, &data->line_len, &data->endian);
	return (0);
}
