/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 03:48:02 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/14 03:48:02 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		size += tex_data[i].line_len * tex_data[i].height;
		++i;
	}
	return (size);
}

void	fill_big_texture(uint8_t *dest, t_vector *textures)
{
	size_t		i;
	size_t		offset;
	t_texture	*data;
	size_t		actual_size;	

	data = textures->data;
	offset = 0;
	i = 0;
	while (i < textures->num_elements)
	{
		actual_size = data[i].line_len * data[i].height;
		ft_memcpy(dest + offset, data[i].pixels, actual_size);
		offset += actual_size;
		++i;
	}
}

int	fill_texture(t_opencl *state, t_scene *scene)
{
	size_t			texture_size;
	uint8_t			*texture;
	int				err;
	static size_t	gpu_size = 0;

	texture_size = get_full_texture_size(&scene->texture);
	texture = malloc(sizeof(cl_uchar) * texture_size);
	if (!texture)
		return (-1);
	fill_big_texture(texture, &scene->texture);
	if (gpu_size < texture_size)
	{
		if (gpu_size > 0)
			clReleaseMemObject(scene->textures);
		scene->textures = clCreateBuffer(state->context, CL_MEM_READ_ONLY,
				sizeof(uint8_t) * texture_size, NULL, &err);
		if (err != CL_SUCCESS)
			return (-1);
		gpu_size = texture_size;
	}
	err = clEnqueueWriteBuffer(state->queue, scene->textures, CL_TRUE,
			0, sizeof(uint8_t) * texture_size, texture, 0, NULL, NULL);
	free(texture);
	return (err);
}
