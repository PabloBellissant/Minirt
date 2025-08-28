/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:15:47 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/28 07:14:28 by jaubry--         ###   ########.fr       */
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

# define LERP_SPEED 0.2f

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
	//data->mouse.warped = true;
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
	setup_key_move_events(data);
	start_mlx_loop(data->mlx, loop, data);
	return (0);
}
