/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_task.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:53:32 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/20 16:53:32 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	schedule_render_task_hook(t_data *data, t_mlx *mlx)
{
	(void)mlx;
	data->ui.export_render_task = true;
}

void	schedule_render_task(t_hbranch *v, t_data *data, t_mlx *mlx)
{
	(void)v;
	(void)mlx;
	data->ui.export_render_task = true;
}

void	export_render_task(t_data *data, t_mlx *mlx)
{
	if (data->ui.export_render_task)
	{
		if (data->ui.ui_toggle)
			data->ui.ui_toggle = false;
		else
		{
			export_to_ppm(data, mlx);
			data->ui.export_render_task = false;
		}
	}
}
