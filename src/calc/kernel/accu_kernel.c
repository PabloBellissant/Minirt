/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accu_kernel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 22:43:01 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/04 22:43:01 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <CL/cl.h>

int	accu_kernel(t_opencl *cl_state, t_data *data, t_img_data *img)
{
	cl_int			err;
	cl_kernel		*kernel;
	const size_t	global_size[2] = {img->width, img->height};

	kernel = &cl_state->kernel.draw_accu;
	err = clSetKernelArg(*kernel, 0, sizeof(cl_mem), &cl_state->bu.accu);
	err |= clSetKernelArg(*kernel, 1, sizeof(cl_mem), &cl_state->bu.img);
	int	sample = data->scene.camera.frame * data->params.exposure;
	err |= clSetKernelArg(*kernel, 2, sizeof(int), &sample);
	err |= clEnqueueNDRangeKernel(cl_state->queue, *kernel, 2, NULL,
			global_size, NULL, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		return (error(pack_err(RT_ID, RT_E_KERNEL), FL, LN, FC));
	err = clEnqueueReadBuffer(cl_state->queue, cl_state->bu.img, CL_TRUE, 0,
			sizeof(int) * img->width * img->height, data->buffers.addr, 0,
			NULL, NULL);
	if (err != CL_SUCCESS)
		return (error(pack_err(RT_ID, RT_E_KERNEL), FL, LN, FC));
	return (0);
}
