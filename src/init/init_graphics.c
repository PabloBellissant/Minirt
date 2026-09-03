/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 02:01:32 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/20 14:45:34 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_graphics(t_data *data)
{
	data->mlx = init_mlx(WIDTH, HEIGHT, TITLE);
	if (!data->mlx)
		return (error(pack_err(MLXW_ID, MLXW_E_INITF), FL, LN, FC));
	data->screen = vec2i(((float)WIDTH / 5.f) * 4.f + 0.5f, HEIGHT);
	data->ui.export_render_task = false;
	return (0);
}
