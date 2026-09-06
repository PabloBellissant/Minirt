/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_selection_zone.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:23:41 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 19:16:32 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_select(t_vec2i mouse_pos[2], t_mlx *mlx_data)
{
	if (mlx_data->mouse_input.focus)
		return ;
	if ((mouse_pos[START].x != 0) && (mouse_pos[START].y != 0))
		ft_mlx_select_put(&mlx_data->img, mouse_pos[START], mouse_pos[END],
			drgb_int(0xFFFFFF));
}
