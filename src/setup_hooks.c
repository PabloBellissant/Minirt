/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:23:06 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 16:29:23 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	setup_key_param_events(t_data *data);
int		setup_mouse_move_events(t_data *data);
void	setup_key_move_events(t_data *data);

int	setup_hooks(t_data *data)
{
	data->mlx->mouse_input.focus = true;
	update_mouse_focus_state(NULL, data->mlx);
	ft_mlx_center_window(data->mlx);
	if (setup_mouse_move_events(data) != 0)
		return (1);
	setup_key_move_events(data);
	setup_key_param_events(data);
	data->params.exposure = 1;
	start_mlx_loop(data->mlx, loop, data);
	return (0);
}
