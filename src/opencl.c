/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_opencl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 08:39:52 by pabellis          #+#    #+#             */
/*   Updated: 2026/01/30 08:39:52 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <CL/cl.h>
#include "bvh.h"
#include "minirt.h"

#define KERNEL_SOURCE \
"#include \"phong.cl\"\n"\
"#include \"calc_rays.cl\"\n"\
"#include \"draw_accu.cl\"\n"\
"#include \"intersect.cl\"\n"\
"#include \"phong_shading.cl\"\n"\
"#include \"sample_texture.cl\"\n"\
"#include \"pbr.cl\"\n"\
"#include \"sample_materials.cl\"\n"\
"#include \"random.cl\"\n"\
"#include \"monte_carlo.cl\"\n"\
"#include \"heat.cl\"\n"\
"#include \"normal_debug.cl\"\n"

static int	init_gpu(t_opencl *state);

int	init_opencl(t_opencl *state, cl_device_type id)
{
	cl_int			err;
	cl_uint			num_platforms;
	cl_platform_id	platforms[8];
	cl_uint			i;

	err = clGetPlatformIDs(8, platforms, &num_platforms);
	if (err != CL_SUCCESS || num_platforms == 0)
		return (-1);
	i = 0;
	while (i < num_platforms)
	{
		err = clGetDeviceIDs(platforms[i], id, 1, &state->device, NULL);
		if (err == CL_SUCCESS)
		{
			state->platform = platforms[i];
			return (init_gpu(state));
		}
		++i;
	}
	return (-1);
}

void	cleanup_opencl(t_opencl *state)
{
	clReleaseKernel(state->kernel.phong);
	clReleaseKernel(state->kernel.normal);
	clReleaseKernel(state->kernel.monte_carlo);
	clReleaseKernel(state->kernel.pbr);
	clReleaseKernel(state->kernel.draw_accu);
	clReleaseKernel(state->kernel.heat);
	clReleaseMemObject(state->bu.accu);
	clReleaseMemObject(state->bu.img);
	clReleaseProgram(state->program);
	clReleaseCommandQueue(state->queue);
	clReleaseContext(state->context);
	free(state->host_buffer);
}

#define KERNEL_COUNT 6

static int	create_kernels(t_opencl *s)
{
	int					err;
	int					i;
	const t_kernel_def	kernels[KERNEL_COUNT] = {
	{"monte_carlo", &s->kernel.monte_carlo},
	{"normal_debug", &s->kernel.normal},
	{"phong", &s->kernel.phong}, {"draw_accu", &s->kernel.draw_accu},
	{"pbr", &s->kernel.pbr},
	{"heat", &s->kernel.heat}};

	i = 0;
	while (i < KERNEL_COUNT)
	{
		*kernels[i].kernel = clCreateKernel(s->program, kernels[i].name, &err);
		if (err != CL_SUCCESS)
		{
			while (i > 0)
			{
				--i;
				clReleaseKernel(*kernels[i].kernel);
			}
			return (-1);
		}
		++i;
	}
	return (0);
}

static int	build_program(t_opencl *state)
{
	int							err;
	const cl_queue_properties	properties[] = {CL_QUEUE_PROPERTIES, 0, 0};

	state->context = clCreateContext(NULL, 1, &state->device, NULL, NULL, &err);
	if (err != CL_SUCCESS)
		return (-1);
	state->queue = clCreateCommandQueueWithProperties(
			state->context, state->device, properties, &err);
	if (err == CL_SUCCESS)
	{
		state->program = clCreateProgramWithSource(
				state->context, 1, (const char *[]){KERNEL_SOURCE}, NULL, &err);
		if (err == CL_SUCCESS)
		{
			err = clBuildProgram(state->program, 1, &state->device,
					"-Ishader -cl-fast-relaxed-math -cl-mad-enable",
					NULL, NULL);
			if (err == CL_SUCCESS)
				return (0);
			clReleaseProgram(state->program);
		}
		clReleaseCommandQueue(state->queue);
	}
	clReleaseContext(state->context);
	return (-1);
}

static int	init_gpu(t_opencl *state)
{
	int	err;

	if (build_program(state) == -1)
		return (-1);
	state->bu.accu = clCreateBuffer(state->context, CL_MEM_READ_WRITE,
			sizeof(cl_float3) * WIDTH * HEIGHT, NULL, &err);
	if (err == CL_SUCCESS)
	{
		state->bu.img = clCreateBuffer(state->context, CL_MEM_READ_WRITE,
				sizeof(int) * WIDTH * HEIGHT, NULL, &err);
		if (err == CL_SUCCESS)
		{
			if (create_kernels(state) == 0)
				return (0);
			clReleaseMemObject(state->bu.img);
		}
		clReleaseMemObject(state->bu.accu);
	}
	clReleaseProgram(state->program);
	clReleaseCommandQueue(state->queue);
	clReleaseContext(state->context);
	return (-1);
}
