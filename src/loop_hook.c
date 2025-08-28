/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:15:47 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/28 20:08:27 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mlx.h"
#include "minirt.h"

static inline bool	is_left_key(int keycode)
{
	return ((keycode == XK_a) || (keycode == XK_Left));
}

static inline bool	is_right_key(int keycode)
{
	return ((keycode == XK_d) || (keycode == XK_Right));
}

static inline bool	is_forward_key(int keycode)
{
	return ((keycode == XK_w) || (keycode == XK_Up));
}

static inline bool	is_backward_key(int keycode)
{
	return ((keycode == XK_s) || (keycode == XK_Down));
}

void	setup_key_move_events(t_data *data)
{
	t_key_event	move_event[5];

	move_event[0] = (t_key_event){.is_key = is_left_key, .action = NULL, .arg = NULL,
		.toggle = false, .status = &(data->keys.left)};
	move_event[1] = (t_key_event){.is_key = is_right_key, .action = NULL, .arg = NULL,
		.toggle = false, .status = &(data->keys.right)};
	move_event[2] = (t_key_event){.is_key = is_forward_key, .action = NULL, .arg = NULL,
		.toggle = false, .status = &(data->keys.forward)};
	move_event[3] = (t_key_event){.is_key = is_backward_key, .action = NULL, .arg = NULL,
		.toggle = false, .status = &(data->keys.backward)};
	move_event[4] = (t_key_event){.is_key = is_space_key, .action = NULL, .arg = NULL,
		.toggle = false, .status = &(data->keys.upward)};
	vector_add(data->mlx->key_input.key_events, move_event, 5);
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
		XGrabPointer(data->mlx->mlx->display, data->mlx->win->window, True, PointerMotionMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);
		mlx_mouse_move(data->mlx->mlx, data->mlx->win, center.x, center.y);
		return (1);
	}
	return (0);
}

/*
float	lerp(float a, float b, float f)
{
//return (a * (1.0 - f) + (b * f)); // more precise
	return (a + f * (b - a));
}
*/

void	handle_camera_rotation(t_data *data, const int delta_x, const int delta_y);

int	mouse_move(int x, int y, t_data *data)
{
	int	delta_x = 0;
	int	delta_y = 0;
	if (data->mouse.warped)
	{
		data->mouse.last_x = data->mlx->half_size.x;
		data->mouse.last_y = data->mlx->half_size.y;
		data->mouse.warped = false;
		return (0);
	}

	if ((x >= data->screen.x) || (y >= data->screen.y)
		|| (x <= data->mlx->origin.x) || (y <= data->mlx->origin.y))
	{
		if (x >= data->screen.x)
			delta_x = x - data->screen.x;
		else if (x <= data->mlx->origin.x)
			delta_x = x - data->mlx->origin.x;
		if (y >= data->screen.y)
			delta_y = y - data->screen.y;
		else if (y <= data->mlx->origin.y)
			delta_y = y - data->mlx->origin.y;
		data->mouse.warped = true;
		mlx_mouse_move(data->mlx->mlx, data->mlx->win, data->mlx->half_size.x, data->mlx->half_size.y);
	}
	else
	{
		delta_x = x - data->mouse.last_x;
		delta_y = y - data->mouse.last_y;
		data->mouse.last_x = x;
		data->mouse.last_y = y;
	}
	if (first_mouse_move(data, data->mlx->half_size))
		return (0);
	handle_camera_rotation(data, delta_x, delta_y);
	return (0);
}

int	loop_hook(t_data *data)
{
	void	*win;
	void	*mlx;

	win = data->mlx->win;
	mlx = data->mlx->mlx;
	mlx_mouse_hide(mlx, win);
	XMoveWindow(data->mlx->mlx->display, data->mlx->win->window, MAX_WIDTH / 2 - (WIDTH / 2), MAX_HEIGHT / 2 - (HEIGHT / 2));
	mlx_hook(win, MotionNotify, PointerMotionMask, mouse_move, data);
	setup_key_move_events(data);
	start_mlx_loop(data->mlx, loop, data);
	return (0);
}
