/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:15:47 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/09 11:16:25 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mlx.h"
#include "minirt.h"

static inline bool	is_left_key(int keycode)
{
	return ((keycode == XK_a));
}

static inline bool	is_right_key(int keycode)
{
	return ((keycode == XK_d));
}

static inline bool	is_forward_key(int keycode)
{
	return ((keycode == XK_w));
}

static inline bool	is_backward_key(int keycode)
{
	return ((keycode == XK_s));
}

static inline bool	is_k_key(int keycode)
{
	return (keycode == XK_k);
}

static inline bool	is_v_key(int keycode)
{
	return (keycode == XK_v);
}

static inline bool	is_up_arrow(int keycode)
{
	return (keycode == XK_Up);
}

static inline bool	is_down_arrow(int keycode)
{
	return (keycode == XK_Down);
}

static inline bool	is_right_arrow(int keycode)
{
	return (keycode == XK_Right);
}

static inline bool	is_left_arrow(int keycode)
{
	return (keycode == XK_Left);
}

static inline bool	is_c_key(int keycode)
{
	return (keycode == XK_c);
}

static inline bool	is_b_key(int keycode)
{
	return (keycode == XK_b);
}

void	setup_key_move_events(t_data *data)
{
	add_status_key_hook(data->mlx, is_left_key, false, &(data->keys.left));
	add_status_key_hook(data->mlx, is_right_key, false, &(data->keys.right));
	add_status_key_hook(data->mlx, is_forward_key, false, &(data->keys.forward));
	add_status_key_hook(data->mlx, is_backward_key, false, &(data->keys.backward));
	add_status_key_hook(data->mlx, is_space_key, false, &(data->keys.upward));
}

void	bvh_depth_increase(t_data *data, t_mlx *mlx)
{
	(void) mlx;
	if (!data->params.bvh_debug)
		return ;
	if (data->params.bvh_depth < 0)
		data->params.bvh_depth = data->scene.bvh.aabb_bvh->depth;
	else
		--data->params.bvh_depth;
	printf("depth: %d\n", data->params.bvh_depth);
}

void	bvh_depth_decrease(t_data *data, t_mlx *mlx)
{
	(void) mlx;
	if (!data->params.bvh_debug)
		return ;
	if (data->params.bvh_depth == data->scene.bvh.aabb_bvh->depth)
		data->params.bvh_depth = -1;
	else
		++data->params.bvh_depth;
	printf("depth: %d\n", data->params.bvh_depth);
}

void	bvh_next_mode(t_data *data, t_mlx *mlx)
{
	(void) mlx;
	if (!data->params.bvh_debug)
		return ;
	if (data->scene.bvh.bvh_mode == 1)
		data->scene.bvh.bvh_mode = 0;
	else
		++data->scene.bvh.bvh_mode;
	load_bvh(data->scene.bvh.bvh_mode, &data->scene); // need security for malloc
	data->params.bvh_depth = data->scene.bvh.aabb_bvh->depth;
}

void	bvh_prev_mode(t_data *data, t_mlx *mlx)
{
	(void) mlx;
	if (!data->params.bvh_debug)
		return ;
	if (data->scene.bvh.bvh_mode == 0)
		data->scene.bvh.bvh_mode = 1;
	else
		--data->scene.bvh.bvh_mode;
	load_bvh(data->scene.bvh.bvh_mode, &data->scene); // need security for malloc
	data->params.bvh_depth = data->scene.bvh.aabb_bvh->depth;
}

void	bvh_color_changer(t_data *data, t_mlx *mlx)
{
	(void) mlx;
	if (!data->params.bvh_debug)
		return ;
	if (data->params.bvh_color_offset <= 1)// pas plutot < 1 ?
		data->params.bvh_color_offset = data->scene.bvh.aabb_bvh->depth;
	else
		--data->params.bvh_color_offset;
	printf("color offset: %d\n", data->params.bvh_color_offset);
}

void	toggle_mouse_focus(void *v, t_mlx *mlx_data)
{
	mlx_data->mouse_input.focus = !mlx_data->mouse_input.focus;
	update_mouse_focus_state(v, mlx_data);
}

void	setup_key_param_events(t_data *data)
{
	add_func_key_hook(data->mlx, is_k_key, toggle_mouse_focus, NULL);
	add_status_key_hook(data->mlx, is_v_key, true, &(data->params.bvh_debug));
	add_status_key_hook(data->mlx, is_b_key, true, &(data->params.bound_debug));
	add_status_key_hook(data->mlx, is_b_key, true, &(data->params.supersampling_debug));
	add_func_key_hook(data->mlx, is_up_arrow, (void (*)(void *, t_mlx *))bvh_depth_increase, data);
	add_func_key_hook(data->mlx, is_down_arrow, (void (*)(void *, t_mlx *))bvh_depth_decrease, data);
	add_func_key_hook(data->mlx, is_right_arrow, (void (*)(void *, t_mlx *))bvh_next_mode, data);
	add_func_key_hook(data->mlx, is_left_arrow, (void (*)(void *, t_mlx *))bvh_prev_mode, data);
	add_func_key_hook(data->mlx, is_c_key, (void (*)(void *, t_mlx *))bvh_color_changer, data);
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
