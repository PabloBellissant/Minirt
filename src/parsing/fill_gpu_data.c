/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_gpu_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:14:48 by pabellis          #+#    #+#             */
/*   Updated: 2026/01/11 21:14:48 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "libft.h"
#include "minirt.h"
#include "object.h"
#include "parsing.h"
#include <CL/cl.h>
#include <CL/cl_platform.h>
#include <stdint.h>
#include <stdio.h>

void	fill_by_tex(t_texture_data *tex_data, size_t i, size_t offset, t_texture *tex)
{
	if (tex_data->index == (int) i)
	{
		tex_data->width = tex[i].width;
		tex_data->height = tex[i].height;
		tex_data->offset = offset;
		tex_data->channels = tex[i].channels;
	}
}

void	update_mat_offset(t_mat *mat, int mat_count, size_t index, size_t offset, t_texture *tex)
{
	size_t	i;

	i = 0;
	while (i < (size_t) mat_count)
	{
		fill_by_tex(&mat[i].kd_id, index, offset, tex);
		fill_by_tex(&mat[i].roughness_id, index, offset, tex);
		fill_by_tex(&mat[i].normal_id, index, offset, tex);
		fill_by_tex(&mat[i].opacity_id, index, offset, tex);
		fill_by_tex(&mat[i].ambient_id, index, offset, tex);
		fill_by_tex(&mat[i].metalness_id, index, offset, tex);
		++i;
	}
}

size_t	get_full_texture_size(t_vector *textures)
{
	size_t		i;
	size_t		size;
	t_texture	*tex_data;

	size = 0;
	tex_data = textures->data;
	i = 0;
	while (i < textures->num_elements)
	{
		size += tex_data[i].width * tex_data[i].height * tex_data[i].channels;
		++i;
	}
	return (size);
}

int	fill_texture_gpu(t_scene *scene, t_mat *mat, t_opencl *state, t_texture_data *skybox_id)
{
	size_t	full_texture_size;
	uint8_t	*big_texture;
	int		err;
	size_t	i;
	size_t	offset;
	t_texture	*tex_data = scene->texture.data;

	full_texture_size = get_full_texture_size(&scene->texture);
	big_texture = malloc(sizeof(cl_uchar) * full_texture_size + 1);
	if (!big_texture)
		return (-1);
	offset = 0;
	i = 0;
	while (i < scene->texture.num_elements)
	{
		ft_memcpy(big_texture + offset, tex_data[i].pixels, tex_data[i].height * tex_data[i].height * tex_data[i].channels);
 		update_mat_offset(mat, scene->mat.num_elements, i, offset, scene->texture.data);
		if (i == (size_t) skybox_id->index)
			skybox_id->offset = offset;
		offset += tex_data[i].height * tex_data[i].width * tex_data[i].channels; 
		++i;
	}
	scene->textures = clCreateBuffer(state->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(uint8_t) * full_texture_size, big_texture, &err);
	free(big_texture);
	if (err != CL_SUCCESS)
		return (-1);
	return (0);
}

int	fill_gpu_data(t_opencl *state, t_scene *scene)
{
	int	err;
	t_object	*data;
	t_sphere	*spheres;
	t_triangle	*triangles;
	t_plane		*planes;

	data = scene->objects.data;
	spheres = malloc(sizeof(t_sphere) * scene->objects.num_elements);
	triangles = malloc(sizeof(t_triangle) * scene->objects.num_elements);
	planes = malloc(sizeof(t_plane) * scene->objects.num_elements);
	size_t	i;

	int	sphere_count;
	int	triangle_count;
	int	planes_count;
	sphere_count = 0;
	triangle_count = 0;
	planes_count = 0;
	i = 0;
	while (i < scene->objects.num_elements)
	{
		if (data[i].type == SPHERE)
		{
			spheres[sphere_count] = data[i].sphere;
			spheres[sphere_count++].mat = data[i].mat_id;
		}
		else if (data[i].type == TRIANGLE)
		{
			triangles[triangle_count] = data[i].triangle;
			triangles[triangle_count++].mat = data[i].mat_id;
		}
		else if (data[i].type == PLANE)
		{
			planes[planes_count] = data[i].plane;
			planes[planes_count++].mat = data[i].mat_id;
		}
		++i;
	}
	t_mat	*mat = malloc(sizeof(t_mat) * scene->mat.num_elements);
	ft_memcpy(mat, scene->mat.data, scene->mat.num_elements * sizeof(t_mat));
	t_texture		*texture = scene->texture.data;
	scene->skybox.index = scene->skybox_tex;
	scene->skybox.width = texture[scene->skybox_tex].width;
	scene->skybox.height = texture[scene->skybox_tex].height;
	scene->skybox.channels = texture[scene->skybox_tex].channels;
	fill_texture_gpu(scene, mat, state, &scene->skybox);
	scene->spheres = clCreateBuffer(state->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(t_sphere) * (sphere_count + 1), spheres, &err);
	scene->triangles = clCreateBuffer(state->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(t_triangle) * (triangle_count + 1), triangles, &err);
	scene->planes = clCreateBuffer(state->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(t_plane) * (planes_count + 1), planes, &err);
	scene->mats = clCreateBuffer(state->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(t_mat) * (scene->mat.num_elements), mat, &err);
	scene->lights = clCreateBuffer(state->context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(t_light) * (scene->light.num_elements), scene->light.data, &err);
	free(mat);
	free(spheres);
	free(triangles);
	free(planes);
	return (0);
}

