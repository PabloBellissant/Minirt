/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_cam_params.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:25:39 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 21:59:37 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	populate_cam_params(t_data *data, t_hbranch *render_edit, int *y_size)
{
	t_block_util	bl;

	bl = (t_block_util){.data = data, .comp = render_edit, .y_size = y_size,
		.clf_ptr = &data->scene.camera.lens_radius, .name = "Lens radius"};
	if (add_slider_edit(bl, 0.f, 0.5f, true) != 0)
		return (1);
	bl = (t_block_util){.data = data, .comp = render_edit, .y_size = y_size,
		.clf_ptr = &data->scene.camera.focus_dist, .name = "Lens distance"};
	if (add_slider_edit(bl, 0.1f, 10000.f, false) != 0)
		return (1);
	return (0);
}
