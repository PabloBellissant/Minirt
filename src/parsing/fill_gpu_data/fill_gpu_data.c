/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_gpu_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:14:48 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/16 21:12:59 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "libft.h"
#include "minirt.h"
#include "object.h"
#include "parsing.h"

int	fill_bvh_data(t_opencl *state, t_scene *scene);
int	fill_object_mem(t_opencl *state, t_scene *scene);

void	fill_by_tex(
	t_texture_data *tex_data, size_t i, size_t offset, t_texture *tex)
{
	if (tex_data->index == (int) i)
	{
		tex_data->width = tex[i].width;
		tex_data->height = tex[i].height;
		tex_data->offset = offset;
		tex_data->channels = tex[i].channels;
	}
}

void	update_mat_offset(
	t_mat *mat, int mat_count, size_t index[2], t_texture *tex)
{
	size_t	i;

	i = 0;
	while (i < (size_t) mat_count)
	{
		fill_by_tex(&mat[i].kd_id, index[0], index[1], tex);
		fill_by_tex(&mat[i].roughness_id, index[0], index[1], tex);
		fill_by_tex(&mat[i].normal_id, index[0], index[1], tex);
		fill_by_tex(&mat[i].opacity_id, index[0], index[1], tex);
		fill_by_tex(&mat[i].ambient_id, index[0], index[1], tex);
		fill_by_tex(&mat[i].metalness_id, index[0], index[1], tex);
		++i;
	}
}

int	fill_texture_gpu(
	t_scene *scene, t_mat *mat, t_opencl *state, t_texture_data *skybox_id)
{
	size_t		i[2];
	t_texture	*tex_data;

	tex_data = scene->texture.data;
	scene->skybox.index = scene->skybox_tex;
	scene->skybox.width = tex_data[scene->skybox_tex].width;
	scene->skybox.height = tex_data[scene->skybox_tex].height;
	scene->skybox.channels = tex_data[scene->skybox_tex].channels;
	if (fill_texture(state, scene) == -1)
		return (-1);
	i[1] = 0;
	i[0] = 0;
	while (i[0] < scene->texture.num_elements)
	{
		update_mat_offset(
			mat, scene->mat.num_elements, i, scene->texture.data);
		if (i[0] == (size_t) skybox_id->index)
			skybox_id->offset = i[1];
		i[1] += tex_data[i[0]].line_len * tex_data[i[0]].height;
		++i[0];
	}
	return (0);
}

int	fill_gpu_data(t_opencl *state, t_scene *scene)
{
	int		err;
	t_mat	*mat_copy;

	if (fill_object_mem(state, scene) == -1)
		return (-1);
	mat_copy = malloc(sizeof(t_mat) * scene->mat.num_elements);
	if (!mat_copy)
		return (-1);
	ft_memcpy(mat_copy, scene->mat.data, scene->mat.num_elements
		* sizeof(t_mat));
	fill_texture_gpu(scene, mat_copy, state, &scene->skybox);
	scene->mats = clCreateBuffer(state->context, CL_MEM_READ_ONLY
			| CL_MEM_COPY_HOST_PTR, sizeof(t_mat) * (scene->mat.num_elements),
			mat_copy, &err);
	scene->lights = clCreateBuffer(state->context, CL_MEM_READ_ONLY
			| CL_MEM_COPY_HOST_PTR, sizeof(t_light)
			* (scene->light.num_elements), scene->light.data, &err);
	scene->bvh.bvh_gpu = clCreateBuffer(state->context, CL_MEM_READ_ONLY
			| CL_MEM_COPY_HOST_PTR, sizeof(t_bvh_node)
			* scene->bvh.world_bvh->nodes.num_elements,
			scene->bvh.world_bvh->nodes.data, &err);
	free(mat_copy);
	return (0);
}

int	free_before_refill(t_scene *scene)
{
	clReleaseMemObject(scene->bvh.bvh_gpu);
	clReleaseMemObject(scene->mats);
	clReleaseMemObject(scene->lights);
	clReleaseMemObject(scene->spheres);
	clReleaseMemObject(scene->triangles);
	clReleaseMemObject(scene->planes);
	return (0);
}
