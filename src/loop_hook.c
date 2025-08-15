/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:15:47 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/15 21:34:04 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mlx.h"
#include "minirt.h"

int	mlx_ext_fullscreen(t_xvar *xvar, t_win_list *win, int fullscreen);

int	key_press(int key_code, t_data *data)
{
	if (RESIZEABLE && (key_code == XK_F11))
	{
		data->fullscreen = !data->fullscreen;
		mlx_ext_fullscreen(data->mlx->mlx, data->mlx->win, data->fullscreen);
	}
	if (key_code == XK_Escape)
		exit(1);
	if ((key_code == XK_a) || (key_code == XK_Left))
		data->keys.left = true;
	if ((key_code == XK_d) || (key_code == XK_Right))
		data->keys.right = true;
	if ((key_code == XK_w) || (key_code == XK_Up))
		data->keys.forward = true;
	if ((key_code == XK_s) || (key_code == XK_Down))
		data->keys.backward = true;
	if (key_code == XK_space)
		data->keys.upward = true;
	if ((key_code == XK_Shift_L) || (key_code == XK_Shift_R))
		data->keys.downward = true;
	return (0);
}

int	key_release(int key_code, t_data *data)
{
	if ((key_code == XK_a) || (key_code == XK_Left))
		data->keys.left = false;
	if ((key_code == XK_d) || (key_code == XK_Right))
		data->keys.right = false;
	if ((key_code == XK_w) || (key_code == XK_Up))
		data->keys.forward = false;
	if ((key_code == XK_s) || (key_code == XK_Down))
		data->keys.backward = false;
	if (key_code == XK_space)
		data->keys.upward = false;
	if ((key_code == XK_Shift_L) || (key_code == XK_Shift_R))
		data->keys.downward = false;
	return (0);
}

static bool	first_mouse_move(t_data *data,
	const int center_x, const int center_y)
{
	static bool	first_move = true;

	if (first_move)
	{
		data->mouse.last_x = center_x;
		data->mouse.last_y = center_y;
		first_move = false;
		mlx_mouse_move(data->mlx->mlx, data->mlx->win, center_x, center_y);
		return (1);
	}
	return (0);
}

#define SENSITIVITY 0.002f
#define MAX_PITCH 1.53938043117523193F

int	mouse_move(int x, int y, t_data *data)
{
	static const int	center_x = WIDTH / 2;
	static const int	center_y = HEIGHT / 2;
	int					delta_x;
	int					delta_y;

	if (first_mouse_move(data, center_x, center_y))
		return (0);
	delta_x = x - center_x;
	delta_y = y - center_y;
	data->scene.camera.rot.y -= delta_x * SENSITIVITY;
	data->scene.camera.rot.x += delta_y * SENSITIVITY;
	if (data->scene.camera.rot.x > MAX_PITCH)
		data->scene.camera.rot.x = MAX_PITCH;
	else if (data->scene.camera.rot.x < -MAX_PITCH)
		data->scene.camera.rot.x = -MAX_PITCH;
	mlx_mouse_move(data->mlx->mlx, data->mlx->win, center_x, center_y);
	data->mouse.last_x = center_x;
	data->mouse.last_y = center_y;
	return (0);
}

int	loop_hook(t_data *data)
{
	void	*win;
	void	*mlx;

	win = data->mlx->win;
	mlx = data->mlx->mlx;
	mlx_mouse_hide(mlx, win);
	mlx_hook(win, MotionNotify, PointerMotionMask, mouse_move, data);
	mlx_hook(win, KeyPress, KeyPressMask, key_press, data);
	mlx_hook(win, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_hook(win, DestroyNotify, StructureNotifyMask, mlx_loop_end, data);
	mlx_loop_hook(mlx, loop, data);
	mlx_loop(mlx);
	return (0);
}
