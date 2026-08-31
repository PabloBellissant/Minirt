/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_hooks1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:25:53 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 17:06:57 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	bvh_depth_increase(t_data *data, t_mlx *mlx)
{
	(void) mlx;
	if (!data->params.bvh_debug)
		return ;
	if (data->params.bvh_depth < 0)
		data->params.bvh_depth = data->scene.bvh.world_bvh->max_depth ;
	else
		--data->params.bvh_depth;
	if (DEBUG)
		printf("depth: %d\n", data->params.bvh_depth);
}

void	bvh_depth_decrease(t_data *data, t_mlx *mlx)
{
	(void) mlx;
	if (!data->params.bvh_debug)
		return ;
	if (data->params.bvh_depth == data->scene.bvh.world_bvh->max_depth)
		data->params.bvh_depth = -1;
	else
		++data->params.bvh_depth;
	if (DEBUG)
		printf("depth: %d\n", data->params.bvh_depth);
}

void	set_render_mode(t_data *data, t_mlx *mlx_data)
{
	*(data->params.render_mode) = mlx_data->key_input.keycode - XK_1;
	if (DEBUG)
		printf("val: %d %d\n", mlx_data->key_input.keycode - XK_1,
			*(data->params.render_mode));
}

void	set_debug_render_mode(t_data *data, t_mlx *mlx_data)
{
	if (mlx_data->key_input.keycode == XK_minus)
		*data->params.render_mode = 4;
	else
		*data->params.render_mode = 5;
}

void	toggle_mouse_focus(void *v, t_mlx *mlx_data)
{
	mlx_data->mouse_input.focus = !mlx_data->mouse_input.focus;
	update_mouse_focus_state(v, mlx_data);
}
