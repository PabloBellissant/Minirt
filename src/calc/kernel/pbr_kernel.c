/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbr_kernel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 21:18:20 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/16 10:02:50 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	set_args(t_opencl *c, cl_kernel *kernel, t_scene *scene);

int	pbr_kernel(t_opencl *c, t_data *data, t_img_data *img)
{
	cl_int			err;
	t_scene			*scene;
	const size_t	global_size[2] = {img->width, img->height};

	scene = &data->scene;
	if (set_args(c, &c->kernel.pbr, scene) != 0)
		return (-1);
	err = clEnqueueNDRangeKernel(c->queue, c->kernel.pbr, 2, NULL,
			global_size, NULL, 0, NULL, NULL);
	err |= clEnqueueReadBuffer(c->queue, c->bu.accu, CL_TRUE, 0,
			sizeof(cl_float3) * img->width * img->height,
			data->buffers.accu, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		return (error(pack_err(RT_ID, RT_E_KERNEL), FL, LN, FC));
	return (0);
}

static int	set_args(t_opencl *c, cl_kernel *kernel, t_scene *scene)
{
	cl_int	err;

	err = clSetKernelArg(*kernel, 0, sizeof(t_camera), &scene->camera);
	err |= clSetKernelArg(
			*kernel, 1, sizeof(cl_mem), &scene->bvh.bvh_gpu);
	err = clSetKernelArg(
			*kernel, 2, sizeof(int), &scene->bvh.world_bvh->shape);
	err |= clSetKernelArg(*kernel, 3, sizeof(cl_mem), &scene->spheres);
	err |= clSetKernelArg(*kernel, 4, sizeof(cl_mem), &scene->triangles);
	err |= clSetKernelArg(*kernel, 5, sizeof(cl_mem), &scene->planes);
	err |= clSetKernelArg(*kernel, 6, sizeof(int), &scene->plane_count);
	err |= clSetKernelArg(*kernel, 7, sizeof(cl_mem), &c->bu.accu);
	err |= clSetKernelArg(*kernel, 8, sizeof(cl_mem), &scene->textures);
	err |= clSetKernelArg(*kernel, 9, sizeof(cl_mem), &scene->mats);
	err |= clSetKernelArg(*kernel, 10, sizeof(cl_mem), &scene->lights);
	err |= clSetKernelArg(*kernel, 11, sizeof(int), &scene->light.num_elements);
	err |= clSetKernelArg(*kernel, 12, sizeof(t_texture_data), &scene->skybox);
	err |= clSetKernelArg(*kernel, 13, sizeof(cl_float3), &scene->ambient);
	if (err != CL_SUCCESS)
		return (error(pack_err(RT_ID, RT_E_KERNEL), FL, LN, FC));
	return (0);
}
