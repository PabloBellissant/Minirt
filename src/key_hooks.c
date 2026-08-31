/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:24:19 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 17:05:32 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline bool	is_roll_key(int keycode)
{
	return (keycode == XK_e || keycode == XK_q);
}

static inline bool	is_render_mode_key(int keycode)
{
	return (keycode == XK_1 || keycode == XK_2
		|| keycode == XK_3 || keycode == XK_4);
}

static inline bool	is_debug_render_mode_key(int keycode)
{
	return (keycode == XK_equal || keycode == XK_minus);
}

void	setup_key_move_events(t_data *data)
{
	add_status_skey_hook(data->mlx, XK_a, false, &(data->keys.left));
	add_status_skey_hook(data->mlx, XK_d, false, &(data->keys.right));
	add_status_skey_hook(data->mlx, XK_w, false, &(data->keys.forward));
	add_status_skey_hook(data->mlx, XK_s, false, &(data->keys.backward));
	add_status_skey_hook(data->mlx, XK_space, false, &(data->keys.upward));
	add_status_skey_hook(data->mlx, XK_q, false, &(data->keys.roll_left));
	add_status_skey_hook(data->mlx, XK_e, false, &(data->keys.roll_right));
}

void	cam_move(t_data *data, t_mlx *mlx_data);
void	export_scene(t_data *data, t_mlx *mlx);
void	schedule_render_task_hook(t_data *data, t_mlx *mlx);
void	bvh_depth_increase(t_data *data, t_mlx *mlx);
void	bvh_depth_decrease(t_data *data, t_mlx *mlx);
void	set_render_mode(t_data *data, t_mlx *mlx_data);
void	set_debug_render_mode(t_data *data, t_mlx *mlx_data);
void	toggle_mouse_focus(void *v, t_mlx *mlx_data);
void	ui_mode(t_data *data, t_mlx *mlx);
void	camera_lens_radius_decrease(t_data *data, t_mlx *mlx);
void	camera_lens_radius_increase(t_data *data, t_mlx *mlx);
void	camera_focus_dist_decrease(t_data *data, t_mlx *mlx);
void	camera_focus_dist_increase(t_data *data, t_mlx *mlx);
void	bvh_color_changer(t_data *data, t_mlx *mlx);

void	increase_exposure(t_data *data, t_mlx *mlx)
{
	data->params.exposure *= 1.3;
	(void) mlx;
}

void	decrease_exposure(t_data *data, t_mlx *mlx)
{
	data->params.exposure /= 1.3;
	(void) mlx;
}

void	setup_key_param_events(t_data *data)
{
	add_func_skey_hook(data->mlx, XK_k, toggle_mouse_focus, NULL);
	add_status_skey_hook(data->mlx, XK_v, true, &(data->params.bvh_debug));
	add_func_skey_hook(data->mlx, XK_m, (t_move_action *)ui_mode, data);
	add_func_skey_hook(data->mlx, XK_F12,
		(t_move_action *)schedule_render_task_hook, data);
	add_func_skey_hook(data->mlx, XK_F11, (t_move_action *)export_scene, data);
	add_func_skey_hook(data->mlx, XK_F5, (t_move_action *)increase_exposure, data);
	add_func_skey_hook(data->mlx, XK_F6, (t_move_action *)decrease_exposure, data);
	add_func_skey_hook(data->mlx, XK_Up,
		(t_move_action *)bvh_depth_increase, data);
	add_func_skey_hook(data->mlx, XK_Down,
		(t_move_action *)bvh_depth_decrease, data);
	add_func_skey_hook(data->mlx, XK_c,
		(t_move_action *)bvh_color_changer, data);
	add_func_skey_hook(data->mlx, XK_t,
		(t_move_action *)camera_focus_dist_increase, data);
	add_func_skey_hook(data->mlx, XK_g,
		(t_move_action *)camera_focus_dist_decrease, data);
	add_func_skey_hook(data->mlx, XK_y,
		(t_move_action *)camera_lens_radius_increase, data);
	add_func_skey_hook(data->mlx, XK_h,
		(t_move_action *)camera_lens_radius_decrease, data);
	add_func_key_hook(data->mlx, is_render_mode_key,
		(t_move_action *)set_render_mode, data);
	add_func_key_hook(data->mlx, is_debug_render_mode_key,
		(t_move_action *)set_debug_render_mode, data);
	add_func_key_hook(data->mlx, is_roll_key, (t_move_action *)cam_move, data);
}
