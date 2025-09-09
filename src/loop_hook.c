/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:15:47 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/09 03:51:58 by jaubry--         ###   ########.fr       */
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

static inline bool	is_k_key(int keycode)
{
	return (keycode == XK_k);
}

static inline bool	is_v_key(int keycode)
{
	return (keycode == XK_v);
}

static inline bool	is_b_key(int keycode)
{
	return (keycode == XK_b);
}

static inline bool	is_c_key(int keycode)
{
	return (keycode == XK_c);
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

void	bvh_depth_changer(t_data *data, t_mlx *mlx)
{
	(void) mlx;
	if (data->params.full_render == true)
		data->params.full_render = false;
	else if (data->params.bvh_depth < 1)
	{
		data->params.full_render = true;
		data->params.bvh_depth = data->scene.bvh->depth;
	}
	else
		--data->params.bvh_depth;
	printf("render: %d depth: %d\n", data->params.full_render, data->params.bvh_depth);
}

void	bvh_color_changer(t_data *data, t_mlx *mlx)
{
	(void) mlx;
	if (data->params.bvh_color_offset <= 1)// pas plutot < 1 ?
		data->params.bvh_color_offset = data->scene.bvh->depth;
	else
		--data->params.bvh_color_offset;
	printf("color offset: %d\n", data->params.bvh_color_offset);
}

void	setup_key_param_events(t_data *data)
{
	t_key_event	param_event[4];
	data->params.full_render = true;

	param_event[0] = (t_key_event){.is_key = is_k_key, .action = update_mouse_focus_state, .arg = NULL,
		.toggle = true, .status = &(data->mlx->mouse_input.focus)};
	param_event[1] = (t_key_event){.is_key = is_v_key, .action = NULL, .arg = NULL,
		.toggle = true, .status = &(data->params.bvh_debug)};
	param_event[2] = (t_key_event){.is_key = is_b_key,
		.action = (void (*)(void *, t_mlx *))bvh_depth_changer, .arg = data,
		.toggle = false, .status = NULL};
	param_event[3] = (t_key_event){.is_key = is_c_key,
		.action = (void (*)(void *, t_mlx *))bvh_color_changer, .arg = data,
		.toggle = false, .status = NULL};
	vector_add(data->mlx->key_input.key_events, param_event, 4);
}

/*
float	lerp(float a, float b, float f)
{
//return (a * (1.0 - f) + (b * f)); // more precise
	return (a + f * (b - a));
}
*/

void	handle_camera_rotation(t_data *data, const int delta_x, const int delta_y);

static inline void	cam_move(t_data *data, t_mlx *mlx_data)
{
	const t_vec2i	delta_pos = vec2i_sub(mlx_data->mouse_input.pos,
										mlx_data->mouse_input.last_pos);
	if (mlx_data->mouse_input.focus)
		handle_camera_rotation(data, delta_pos.x, delta_pos.y);
}

void	setup_mouse_move_events(t_data *data)
{
	t_mouse_event	move_event;

	move_event = (t_mouse_event){.action = (void (*)(void *, t_mlx *))cam_move,
		.arg = data};
	vector_add(data->mlx->mouse_input.move_events, &move_event, 1);
}

int	loop_hook(t_data *data)
{
	data->mlx->mouse_input.focus = true;
	update_mouse_focus_state(NULL, data->mlx);
	ft_mlx_center_window(data->mlx);
	setup_mouse_move_events(data);
	setup_key_move_events(data);
	setup_key_param_events(data);
	start_mlx_loop(data->mlx, loop, data);
	return (0);
}
