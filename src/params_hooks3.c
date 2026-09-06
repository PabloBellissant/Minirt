/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_hooks3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 05:15:47 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/20 16:29:41 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	bvh_color_changer(t_data *data, t_mlx *mlx)
{
	(void) mlx;
	data->params.color_offset++;
	if (DEBUG)
		printf("color : %d\n", data->params.color_offset);
}
