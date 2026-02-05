/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 22:56:09 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/04 22:56:09 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	pbr_render(t_data *data, t_img_data *img)
{
	t_camera	*cam;
	static int	frame;

	cam = &data->scene.camera;
	if (cam_has_moved(cam) || render_changed(data) || frame == 0)
	{
		frame = 0;
		clEnqueueFillBuffer(data->cl.queue, data->cl.bu.accu,
			&(cl_float3){.x = 0, .y = 0, .z = 0}, sizeof(cl_float3),
			0, sizeof(cl_float3) * WIDTH * HEIGHT, 0, NULL, NULL);
		fill_camera(cam, img);
	}
	++frame;
	cam->frame = frame;
	if (pbr_kernel(&data->cl, data, img) != 0)
		return ;
	accu_kernel(&data->cl, data, img);
}
