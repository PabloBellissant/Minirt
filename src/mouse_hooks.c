/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:23:40 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 17:06:48 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_camera_rotation(t_data *data, const int delta_x,
			const int delta_y);

void	cam_move(t_data *data, t_mlx *mlx_data)
{
	const t_vec2i	delta_pos = vec2i_sub(mlx_data->mouse_input.pos,
			mlx_data->mouse_input.last_pos);

	mlx_data->mouse_input.last_pos = mlx_data->mouse_input.pos;
	if (mlx_data->mouse_input.focus)
		handle_camera_rotation(data, delta_pos.x, delta_pos.y);
}

void	select_mouse_pos(t_vec2i mouse_pos[2], t_mlx *mlx_data);
void	select_zone(t_vec2i pos, t_maction action,
			t_data *data, t_mlx *mlx_data);

int	setup_mouse_move_events(t_data *data)
{
	if (add_func_move_hook(data->mlx, (t_move_action *)cam_move, data) < 0)
		return (error(pack_err(MLXW_ID, MLXW_E_EVENTH), FL, LN, FC));
	if (add_func_move_hook(data->mlx, (t_move_action *)select_mouse_pos,
			data->ui.selection.mouse_pos) < 0)
		return (error(pack_err(MLXW_ID, MLXW_E_EVENTH), FL, LN, FC));
	if (add_func_button_hook(data->mlx, MLCLICK,
			(t_button_action *)select_zone, data) < 0)
		return (error(pack_err(MLXW_ID, MLXW_E_EVENTH), FL, LN, FC));
	return (0);
}
