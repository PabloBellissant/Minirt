/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:15:47 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 05:01:36 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mlx.h"
#include "minirt.h"

int	mlx_ext_fullscreen(t_xvar *xvar, t_win_list *win, int fullscreen);

int	key_press(int key_code, t_data *mlx)
{
	if (key_code == XK_F11)
	{
		mlx->fullscreen = !mlx->fullscreen;
		mlx_ext_fullscreen(mlx->mlx, mlx->win, mlx->fullscreen);
	}
	if (key_code == XK_Escape)
		exit(1);
	if ((key_code == XK_a) || (key_code == XK_Left))
		mlx->keys.left = true;
	if ((key_code == XK_d) || (key_code == XK_Right))
		mlx->keys.right = true;
	if ((key_code == XK_w) || (key_code == XK_Up))
		mlx->keys.forward = true;
	if ((key_code == XK_s) || (key_code == XK_Down))
		mlx->keys.backward = true;
	if (key_code == XK_space)
		mlx->keys.upward = true;
	if ((key_code == XK_Shift_L) || (key_code == XK_Shift_R))
		mlx->keys.downward = true;
	return (0);
}

int	key_release(int key_code, t_data *mlx)
{
	if ((key_code == XK_a) || (key_code == XK_Left))
		mlx->keys.left = false;
	if ((key_code == XK_d) || (key_code == XK_Right))
		mlx->keys.right = false;
	if ((key_code == XK_w) || (key_code == XK_Up))
		mlx->keys.forward = false;
	if ((key_code == XK_s) || (key_code == XK_Down))
		mlx->keys.backward = false;
	if (key_code == XK_space)
		mlx->keys.upward = false;
	if ((key_code == XK_Shift_L) || (key_code == XK_Shift_R))
		mlx->keys.downward = false;
	return (0);
}

static bool	first_mouse_move(t_data *mlx,
	const int center_x, const int center_y)
{
	static bool	first_move = true;

	if (first_move)
	{
		mlx->mouse.last_x = center_x;
		mlx->mouse.last_y = center_y;
		first_move = false;
		mlx_mouse_move(mlx->mlx, mlx->win, center_x, center_y);
		return (1);
	}
	return (0);
}

#define SENSITIVITY 0.002f
#define MAX_PITCH 1.53938043117523193F

int	mouse_move(int x, int y, t_data *mlx)
{
	static const int	center_x = WIDTH / 2;
	static const int	center_y = HEIGHT / 2;
	int					delta_x;
	int					delta_y;

	if (first_mouse_move(mlx, center_x, center_y))
		return (0);
	delta_x = x - center_x;
	delta_y = y - center_y;
	mlx->scene.camera.rot.y -= delta_x * SENSITIVITY;
	mlx->scene.camera.rot.x += delta_y * SENSITIVITY;
	if (mlx->scene.camera.rot.x > MAX_PITCH)
		mlx->scene.camera.rot.x = MAX_PITCH;
	else if (mlx->scene.camera.rot.x < -MAX_PITCH)
		mlx->scene.camera.rot.x = -MAX_PITCH;
	mlx_mouse_move(mlx->mlx, mlx->win, center_x, center_y);
	mlx->mouse.last_x = center_x;
	mlx->mouse.last_y = center_y;
	return (0);
}

int	loop_hook(t_data *mlx)
{
	void	*win;

	win = mlx->win;
	mlx_mouse_hide(mlx->mlx, win);
	mlx_hook(win, MotionNotify, PointerMotionMask, mouse_move, mlx);
	mlx_hook(win, KeyPress, KeyPressMask, key_press, mlx);
	mlx_hook(win, KeyRelease, KeyReleaseMask, key_release, mlx);
	mlx_hook(win, DestroyNotify, StructureNotifyMask, mlx_loop_end, mlx->mlx);
	mlx_loop_hook(mlx->mlx, loop, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
