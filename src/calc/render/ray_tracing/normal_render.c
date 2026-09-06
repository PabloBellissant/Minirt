/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 23:54:39 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/07 05:44:29 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	normal_render(t_data *data, t_img_data *img)
{
	t_camera	*cam;
	static int	frame;

	cam = &data->scene.camera;
	if (cam_has_moved(cam) || render_changed(data) || frame == 0)
	{
		frame = 0;
		clEnqueueFillBuffer(data->cl.queue, data->cl.bu.accu,
			&(cl_float3){.x = 0, .y = 0, .z = 0}, sizeof(cl_float3), 0,
			sizeof(cl_float3) * img->width * img->height, 0, NULL, NULL);
		fill_camera(cam, img);
	}
	++frame;
	cam->frame = frame;
	if (normal_kernel(&data->cl, data, &data->mlx->img) != 0)
		return (1);
	if (accu_kernel(&data->cl, data, &data->mlx->img) != 0)
		return (1);
	return (0);
}
