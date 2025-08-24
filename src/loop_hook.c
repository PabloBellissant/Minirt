/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:15:47 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/24 16:33:22 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mlx.h"
#include "minirt.h"

int	key_press(int key_code, t_data *data)
{
	if (RESIZEABLE && (key_code == XK_F11))
	{
		data->mlx->fullscreen = !data->mlx->fullscreen;
		mlx_ext_fullscreen(data->mlx->mlx, data->mlx->win, data->mlx->fullscreen);
	}
	if (key_code == XK_Escape)
		mlx_loop_end(data->mlx->mlx);
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
	if ((key_code == XK_Control_L) || (key_code == XK_Control_R))
		data->keys.run = true;
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
	if ((key_code == XK_Control_L) || (key_code == XK_Control_R))
		data->keys.run = false;
	return (0);
}

static bool	first_mouse_move(t_data *data,
	const t_vec2i center)
{
	static bool	first_move = true;

	if (first_move)
	{
		data->mouse.last_x = center.x;
		data->mouse.last_y = center.y;
		first_move = false;
		data->mouse.warped = true;
		mlx_mouse_move(data->mlx->mlx, data->mlx->win, center.x, center.y);
		return (1);
	}
	return (0);
}

float	lerp(float a, float b, float f)
{
//return (a * (1.0 - f) + (b * f)); // more precise
	return (a + f * (b - a));
}

void	handle_camera_rotation(t_data *data, const float delta_x, const float delta_y);

# define LERP_SPEED 0.1f

int	mouse_move(int x, int y, t_data *data)
{
	if (data->mouse.warped)
	{
		data->mouse.warped = false;
		return (0);
	}
	const float	delta_x = lerp(data->mlx->half_size.x, x, LERP_SPEED * data->mlx->delta_time) - data->mlx->half_size.x;
	const float	delta_y = lerp(data->mlx->half_size.y, y, LERP_SPEED * data->mlx->delta_time) - data->mlx->half_size.y;
	if (first_mouse_move(data, data->mlx->half_size))
		return (0);

	handle_camera_rotation(data, delta_x, delta_y);
	data->mouse.warped = true;
	mlx_mouse_move(data->mlx->mlx, data->mlx->win, data->mlx->half_size.x, data->mlx->half_size.y);
	data->mouse.last_x = data->mlx->half_size.x;
	data->mouse.last_y = data->mlx->half_size.y;
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
	start_mlx_loop(data->mlx, loop, data);
	return (0);
}
