/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_hooks2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:26:00 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 16:26:28 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	camera_focus_dist_increase(t_data *data, t_mlx *mlx)
{
	(void) mlx;
	data->scene.camera.focus_dist *= 1.05f;
	if (data->scene.camera.focus_dist > 10000)
		data->scene.camera.focus_dist = 10000;
	if (DEBUG)
		printf("focus_dist : %f\n", data->scene.camera.focus_dist);
}

void	camera_focus_dist_decrease(t_data *data, t_mlx *mlx)
{
	(void) mlx;
	data->scene.camera.focus_dist /= 1.05f;
	if (data->scene.camera.focus_dist < 0.2f)
		data->scene.camera.focus_dist = 0.2f;
	if (DEBUG)
		printf("focus_dist : %f\n", data->scene.camera.focus_dist);
}

void	camera_lens_radius_increase(t_data *data, t_mlx *mlx)
{
	(void) mlx;
	data->scene.camera.lens_radius *= 1.05f;
	if (data->scene.camera.lens_radius > 0.5f)
		data->scene.camera.lens_radius = 0.5f;
	if (DEBUG)
		printf("lens_radius : %f\n", data->scene.camera.lens_radius);
}

void	camera_lens_radius_decrease(t_data *data, t_mlx *mlx)
{
	(void) mlx;
	data->scene.camera.lens_radius /= 1.05f;
	if (data->scene.camera.lens_radius < 0.0f)
		data->scene.camera.lens_radius = 0.0f;
	if (DEBUG)
		printf("lens_radius : %f\n", data->scene.camera.lens_radius);
}

void	ui_mode(t_data *data, t_mlx *mlx)
{
	(void)mlx;
	data->params.ui_mode = (data->params.ui_mode + 1) % 3;
	if (data->params.ui_mode == 1)
	{
		*data->ui.lpannel_toggle = false;
		data->ui.render_switch->pos = vec2i(WIDTH - 15, 15);
		precompute_button_group(data->ui.render_switch);
		precompute_hbranch(data->ui.render_switch);
	}
	else if (data->params.ui_mode == 2)
		*data->ui.ui_toggle = false;
	else
	{
		*data->ui.lpannel_toggle = true;
		*data->ui.ui_toggle = true;
		data->ui.render_switch->pos = vec2i(data->screen.x - 15, 15);
		precompute_button_group(data->ui.render_switch);
		precompute_hbranch(data->ui.render_switch);
	}
}
