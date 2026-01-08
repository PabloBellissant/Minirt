/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:15:47 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/15 04:44:06 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mlx.h"
#include "minirt.h"
#include "mlx_detect_special_key.h"
#include "mlx_key_input.h"

static inline bool	is_roll_key(int keycode)
{
	return (keycode == XK_e || keycode == XK_q);
}

static inline bool	is_render_mode_key(int keycode)
{
	return ((keycode == XK_1) || (keycode == XK_2) || (keycode == XK_3) || (keycode == XK_4));
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

void	set_render_mode(t_data *data, t_mlx *mlx_data)
{
	data->params.render_mode = mlx_data->key_input.keycode - XK_1;
}

void	toggle_mouse_focus(void *v, t_mlx *mlx_data)
{
	mlx_data->mouse_input.focus = !mlx_data->mouse_input.focus;
	update_mouse_focus_state(v, mlx_data);
}

static inline void	cam_move(t_data *data, t_mlx *mlx_data);
void	export_scene(t_data *data, t_mlx *mlx);

void	setup_key_param_events(t_data *data)
{
	add_func_skey_hook(data->mlx, XK_k, toggle_mouse_focus, NULL);
	add_status_skey_hook(data->mlx, XK_v, true, &(data->params.bvh_debug));
	add_status_skey_hook(data->mlx, XK_n, true, &(data->params.normal_debug));
	add_status_skey_hook(data->mlx, XK_i, true, &(data->params.smooth_shading));
	add_status_skey_hook(data->mlx, XK_Return, true, &(data->params.quality_render));
	add_status_skey_hook(data->mlx, XK_F12, true, &(data->params.exporting));
	add_status_skey_hook(data->mlx, XK_t, true, &(data->params.texture));
	add_status_skey_hook(data->mlx, XK_m, true, &(data->params.normal_map));
	add_status_skey_hook(data->mlx, XK_b, true, &(data->params.ambient));
	add_func_skey_hook(data->mlx, XK_F11, (void (*)(void *, t_mlx *))export_scene, data);
	add_func_skey_hook(data->mlx, XK_Up, (void (*)(void *, t_mlx *))bvh_depth_increase, data);
	add_func_skey_hook(data->mlx, XK_Down, (void (*)(void *, t_mlx *))bvh_depth_decrease, data);
	add_func_skey_hook(data->mlx, XK_Right, (void (*)(void *, t_mlx *))bvh_next_mode, data);
	add_func_skey_hook(data->mlx, XK_Left, (void (*)(void *, t_mlx *))bvh_prev_mode, data);
	add_func_skey_hook(data->mlx, XK_c, (void (*)(void *, t_mlx *))bvh_color_changer, data);
	add_func_key_hook(data->mlx, is_render_mode_key, (void (*)(void *, t_mlx *))set_render_mode, data);
	add_func_key_hook(data->mlx, is_roll_key, (void (*)(void *, t_mlx *))cam_move, data);
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
	t_move_event	move_event;

	move_event = (t_move_event){.action = (void (*)(void *, t_mlx *))cam_move,
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
