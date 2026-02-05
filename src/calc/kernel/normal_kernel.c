/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_kernel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 21:06:19 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/04 21:06:19 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <CL/cl.h>

int	normal_kernel(t_opencl *cl_state, t_data *data, t_img_data *img)
{
	const size_t	global_size[2] = {img->width, img->height};
	cl_kernel		*kernel;
	int				err;

	kernel = &cl_state->kernel.normal;
	err = clSetKernelArg(*kernel, 0, sizeof(t_camera), &data->scene.camera);
	err |= clSetKernelArg(*kernel, 1, sizeof(cl_mem), &data->scene.spheres);
	err |= clSetKernelArg(
			*kernel, 2, sizeof(cl_mem), &data->scene.bvh.sphere_gpu_bvh);
	err |= clSetKernelArg(*kernel, 3, sizeof(cl_mem), &data->scene.triangles);
	err |= clSetKernelArg(
			*kernel, 4, sizeof(cl_mem), &data->scene.bvh.triangle_gpu_bvh);
	err |= clSetKernelArg(*kernel, 5, sizeof(cl_mem), &data->scene.planes);
	err |= clSetKernelArg(*kernel, 6, sizeof(int), &data->scene.plane_count);
	err |= clSetKernelArg(*kernel, 7, sizeof(cl_mem), &cl_state->bu.accu);
	err |= clSetKernelArg(*kernel, 8, sizeof(cl_mem), &data->scene.textures);
	err |= clSetKernelArg(*kernel, 9, sizeof(cl_mem), &data->scene.mats);
	err |= clEnqueueNDRangeKernel(cl_state->queue, *kernel, 2, NULL,
			global_size, NULL, 0, NULL, NULL);
	err |= clEnqueueReadBuffer(cl_state->queue, cl_state->bu.accu, CL_TRUE, 0,
			sizeof(cl_float3) * img->width * img->height, data->buffers.accu, 0,
			NULL, NULL);
	if (err != CL_SUCCESS)
		return (error(pack_err(RT_ID, RT_E_KERNEL), FL, LN, FC));
	return (0);
}
