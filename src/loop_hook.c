/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:15:47 by pabellis          #+#    #+#             */
/*   Updated: 2026/01/19 19:29:23 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mlx.h"
#include "minirt.h"
#include "mlx_detect_input_key.h"
#include "mlx_detect_special_key.h"
#include "mlx_key_input.h"

static inline bool	is_roll_key(int keycode)
{
	return (keycode == XK_e || keycode == XK_q);
}

static inline bool	is_render_mode_key(int keycode)
{
	return (keycode == XK_1 || keycode == XK_2 || keycode == XK_3 || keycode == XK_4);
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

void	bvh_depth_increase(t_data *data, t_mlx *mlx)
{
	int	depth;

	depth = max(data->scene.bvh.sphere_bvh->depth,
							  data->scene.bvh.triangle_bvh->depth);
	(void) mlx;
	if (!data->params.bvh_debug)
		return ;
	if (data->params.bvh_depth < 0)
		data->params.bvh_depth = depth;
	else
		--data->params.bvh_depth;
	printf("depth: %d\n", data->params.bvh_depth);
}

void	bvh_depth_decrease(t_data *data, t_mlx *mlx)
{
	int	depth;

	depth = max(data->scene.bvh.sphere_bvh->depth,
							  data->scene.bvh.triangle_bvh->depth);
	(void) mlx;
	if (!data->params.bvh_debug)
		return ;
	if (data->params.bvh_depth == depth)
		data->params.bvh_depth = -1;
	else
		++data->params.bvh_depth;
	printf("depth: %d\n", data->params.bvh_depth);
}

#define BVH_MODES 2

void	update_bvh_mode(t_data *data)
{
	data->scene.bvh.sphere_bvh = NULL;
	data->params.bvh_depth = max(data->scene.bvh.sphere_bvh->depth,
							  data->scene.bvh.triangle_bvh->depth);
}

void	bvh_next_mode(t_data *data, t_mlx *mlx)
{
	(void) mlx;
	if (!data->params.bvh_debug)
		return ;
	if (data->scene.bvh.bvh_mode == BVH_MODES)
		data->scene.bvh.bvh_mode = 0;
	else
		++data->scene.bvh.bvh_mode;
	update_bvh_mode(data);
}

void	bvh_prev_mode(t_data *data, t_mlx *mlx)
{
	(void) mlx;
	if (!data->params.bvh_debug)
		return ;
	if (data->scene.bvh.bvh_mode == 0)
		data->scene.bvh.bvh_mode = BVH_MODES;
	else
		--data->scene.bvh.bvh_mode;
	update_bvh_mode(data);
}

void	bvh_color_changer(t_data *data, t_mlx *mlx)
{
	(void) mlx;
	++data->params.bvh_color_offset;
	printf("color offset: %d\n", data->params.bvh_color_offset);
}

void	set_render_mode(t_data *data, t_mlx *mlx_data)
{
	data->params.render_mode = mlx_data->key_input.keycode - XK_1;
}

void	set_debug_render_mode(t_data *data, t_mlx *mlx_data)
{
	if (mlx_data->key_input.keycode == XK_minus)
		data->params.render_mode = 4;
	else
		data->params.render_mode = 5;
}

void	toggle_mouse_focus(void *v, t_mlx *mlx_data)
{
	mlx_data->mouse_input.focus = !mlx_data->mouse_input.focus;
	update_mouse_focus_state(v, mlx_data);
}

void	camera_focus_dist_increase(t_data *data, t_mlx *mlx)
{
	(void) mlx;
	data->scene.camera.focus_dist *= 1.05f;
	if (data->scene.camera.focus_dist > 10000)
		data->scene.camera.focus_dist = 10000;
	printf("focus_dist : %f\n", data->scene.camera.focus_dist);
}

void	camera_focus_dist_decrease(t_data *data, t_mlx *mlx)
{
	(void) mlx;
	data->scene.camera.focus_dist /= 1.05f;
	if (data->scene.camera.focus_dist < 0.2f)
		data->scene.camera.focus_dist = 0.2f;
	printf("focus_dist : %f\n", data->scene.camera.focus_dist);
}

void	camera_lens_radius_increase(t_data *data, t_mlx *mlx)
{
	(void) mlx;
	data->scene.camera.lens_radius *= 1.05f;
	if (data->scene.camera.lens_radius > 0.5f)
		data->scene.camera.lens_radius = 0.5f;
	printf("lens_radius : %f\n", data->scene.camera.lens_radius);
}

void	camera_lens_radius_decrease(t_data *data, t_mlx *mlx)
{
	(void) mlx;
	data->scene.camera.lens_radius /= 1.05f;
	if (data->scene.camera.lens_radius < 0.0f)
		data->scene.camera.lens_radius = 0.0f;
	printf("lens_radius : %f\n", data->scene.camera.lens_radius);
}


static inline void	cam_move(t_data *data, t_mlx *mlx_data);
void	export_scene(t_data *data, t_mlx *mlx);

void	setup_key_param_events(t_data *data)
{
	add_func_skey_hook(data->mlx, XK_k, toggle_mouse_focus, NULL);
	add_status_skey_hook(data->mlx, XK_v, true, &(data->params.bvh_debug));
	add_func_skey_hook(data->mlx, XK_F12, (void (*)(void *, t_mlx *))export_to_ppm, data);
	add_func_skey_hook(data->mlx, XK_F11, (void (*)(void *, t_mlx *))export_scene, data);
	add_func_skey_hook(data->mlx, XK_Up, (void (*)(void *, t_mlx *))bvh_depth_increase, data);
	add_func_skey_hook(data->mlx, XK_Down, (void (*)(void *, t_mlx *))bvh_depth_decrease, data);
	add_func_skey_hook(data->mlx, XK_Right, (void (*)(void *, t_mlx *))bvh_next_mode, data);
	add_func_skey_hook(data->mlx, XK_Left, (void (*)(void *, t_mlx *))bvh_prev_mode, data);
	add_func_skey_hook(data->mlx, XK_c, (void (*)(void *, t_mlx *))bvh_color_changer, data);
	add_func_skey_hook(data->mlx, XK_t, (void (*)(void *, t_mlx *))camera_focus_dist_increase, data);
	add_func_skey_hook(data->mlx, XK_g, (void (*)(void *, t_mlx *))camera_focus_dist_decrease, data);
	add_func_skey_hook(data->mlx, XK_y, (void (*)(void *, t_mlx *))camera_lens_radius_increase, data);
	add_func_skey_hook(data->mlx, XK_h, (void (*)(void *, t_mlx *))camera_lens_radius_decrease, data);
	add_func_key_hook(data->mlx, is_render_mode_key, (void (*)(void *, t_mlx *))set_render_mode, data);
	add_func_key_hook(data->mlx, is_debug_render_mode_key, (void (*)(void *, t_mlx *))set_debug_render_mode, data);
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
	t_vec2i	delta_pos = vec2i_sub(mlx_data->mouse_input.pos,
										mlx_data->mouse_input.last_pos);
	mlx_data->mouse_input.last_pos = mlx_data->mouse_input.pos;
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
	//if (create_aabb_bvh_sah(&data->scene) != 0)
	//	return (1);
	start_mlx_loop(data->mlx, loop, data);
	return (0);
}
