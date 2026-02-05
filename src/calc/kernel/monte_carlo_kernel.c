/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monte_carlo_kernel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 19:41:32 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/04 19:41:32 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "minirt.h"
#include <CL/cl.h>

static int	set_args(t_opencl *c, cl_kernel *kernel, t_scene *scene);

int	monte_carlo_kernel(t_opencl *cl_state, t_data *data, t_img_data *img)
{
	cl_int			err;
	const size_t	global_size[2] = {img->width, img->height};

	if (set_args(cl_state, &cl_state->kernel.monte_carlo, &data->scene) != 0)
		return (-1);
	err = clEnqueueNDRangeKernel(cl_state->queue, cl_state->kernel.monte_carlo,
			2, NULL, global_size, NULL, 0, NULL, NULL);
	err |= clEnqueueReadBuffer(cl_state->queue, cl_state->bu.accu, CL_TRUE, 0,
			sizeof(cl_float3) * img->width * img->height, data->buffers.accu,
			0, NULL, NULL);
	if (err != CL_SUCCESS)
		return (error(pack_err(RT_ID, RT_E_KERNEL), FL, LN, FC));
	return (0);
}

static int	set_args(t_opencl *c, cl_kernel *kernel, t_scene *scene)
{
	cl_int	err;
	int		random;

	random = rand();
	err = clSetKernelArg(*kernel, 0, sizeof(t_camera), &scene->camera);
	err |= clSetKernelArg(*kernel, 1, sizeof(cl_mem), &scene->spheres);
	err |= clSetKernelArg(
			*kernel, 2, sizeof(cl_mem), &scene->bvh.sphere_gpu_bvh);
	err |= clSetKernelArg(*kernel, 3, sizeof(cl_mem), &scene->triangles);
	err |= clSetKernelArg(
			*kernel, 4, sizeof(cl_mem), &scene->bvh.triangle_gpu_bvh);
	err |= clSetKernelArg(*kernel, 5, sizeof(cl_mem), &scene->planes);
	err |= clSetKernelArg(*kernel, 6, sizeof(int), &scene->plane_count);
	err |= clSetKernelArg(*kernel, 7, sizeof(cl_mem), &c->bu.accu);
	err |= clSetKernelArg(*kernel, 8, sizeof(cl_mem), &scene->textures);
	err |= clSetKernelArg(*kernel, 9, sizeof(cl_mem), &scene->mats);
	err |= clSetKernelArg(*kernel, 10, sizeof(cl_mem), &scene->lights);
	err |= clSetKernelArg(*kernel, 11, sizeof(int), &scene->light.num_elements);
	err |= clSetKernelArg(*kernel, 12, sizeof(t_texture_data), &scene->skybox);
	err |= clSetKernelArg(*kernel, 13, sizeof(int), &random);
	if (err != CL_SUCCESS)
		return (error(pack_err(RT_ID, RT_E_KERNEL), FL, LN, FC));
	return (0);
}
