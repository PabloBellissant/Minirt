/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_kernel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 22:48:56 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/04 22:48:56 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	heat_kernel(t_opencl *cl_state, t_data *data, t_img_data *img)
{
	const size_t	global_size[2] = {img->width, img->height};
	cl_kernel		k;
	cl_int			err;
	t_scene			*scene;

	k = cl_state->kernel.heat;
	scene = &data->scene;
	err = clSetKernelArg(k, 0, sizeof(t_camera), &scene->camera);
	err |= clSetKernelArg(k, 1, sizeof(cl_mem), &scene->bvh.sphere_gpu_bvh);
	err |= clSetKernelArg(k, 2, sizeof(cl_mem), &scene->bvh.triangle_gpu_bvh);
	err |= clSetKernelArg(k, 3, sizeof(cl_mem), &cl_state->bu.accu);
	err |= clSetKernelArg(k, 4, sizeof(int), &scene->bvh.triangle_bvh->depth);
	err |= clSetKernelArg(k, 5, sizeof(int), &data->params.bvh_color_offset);
	if (err != CL_SUCCESS)
		return (error(pack_err(RT_ID, RT_E_KERNEL), FL, LN, FC));
	err = clEnqueueNDRangeKernel(cl_state->queue, k, 2, NULL,
			global_size, NULL, 0, NULL, NULL);
	err |= clEnqueueReadBuffer(cl_state->queue, cl_state->bu.accu, CL_TRUE, 0,
			sizeof(cl_float3) * img->width * img->height, data->buffers.accu,
			0, NULL, NULL);
	if (err != CL_SUCCESS)
		return (error(pack_err(RT_ID, RT_E_KERNEL), FL, LN, FC));
	return (0);
}
