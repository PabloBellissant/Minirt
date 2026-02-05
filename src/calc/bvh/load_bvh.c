/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_bvh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 23:53:50 by pabellis          #+#    #+#             */
/*   Updated: 2026/01/20 17:07:37 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "bvh.h"

int	load_bvh(int mode, t_scene *scene, t_opencl *state)
{
	int	err;

	free(scene->bvh.sphere_bvh);
	free(scene->bvh.triangle_bvh);
	if (mode == 0)
	{
		if (create_sphere_bvh(scene) == -1)
			return (-1);
	}
	else if (mode == 1)
	{
		if (create_aabb_bvh_sah(scene) == -1)
			return (-1);
		/*
		for (int i = 0; i < scene->bvh.triangle_bvh_size; ++i)
		    printf("%d: depth=%d next=%d object=%d min=(%f,%f,%f) max=(%f,%f,%f)\n",
	           i, scene->bvh.triangle_bvh[i].depth, scene->bvh.triangle_bvh[i].next, scene->bvh.triangle_bvh[i].object,
	           scene->bvh.triangle_bvh[i].min.x, scene->bvh.triangle_bvh[i].min.y, scene->bvh.triangle_bvh[i].min.z,
	           scene->bvh.triangle_bvh[i].max.x, scene->bvh.triangle_bvh[i].max.y, scene->bvh.triangle_bvh[i].max.z);
	    */

	}
	if (false)
	{
		scene->bvh.sphere_gpu_bvh = clCreateBuffer(state->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(t_aabb_bvh) * scene->bvh.sphere_bvh4_size, scene->bvh.sphere_bvh4, &err);
		scene->bvh.triangle_gpu_bvh = clCreateBuffer(state->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(t_aabb_bvh) * scene->bvh.triangle_bvh4_size, scene->bvh.triangle_bvh4, &err);
	}
	else
	{
		scene->bvh.sphere_gpu_bvh = clCreateBuffer(state->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(t_aabb_bvh) * scene->bvh.sphere_bvh_size, scene->bvh.sphere_bvh, &err);
		scene->bvh.triangle_gpu_bvh = clCreateBuffer(state->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(t_aabb_bvh) * scene->bvh.triangle_bvh_size, scene->bvh.triangle_bvh, &err);
	}
	return (0);
}
