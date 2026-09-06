/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:37:17 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 17:08:59 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_textures(t_vector *vec)
{
	size_t		i;
	t_texture	*texture;

	texture = vec->data;
	i = 0;
	while (i < vec->num_elements)
	{
		free(texture[i].addr);
		free(texture[i].name);
		++i;
	}
	free_vector(vec);
}

void	free_mats(t_vector *vec)
{
	size_t		i;
	t_mat		*mat;

	mat = vec->data;
	i = 0;
	while (i < vec->num_elements)
	{
		free(mat[i].name);
		++i;
	}
	free_vector(vec);
}

void	free_scene(t_scene *scene)
{
	free_vector(&scene->light);
	free_vector(&scene->objects);
	free_textures(&scene->texture);
	free_mats(&scene->mat);
	free_vector(&scene->mtl_list);
	free_bvh(scene->bvh);
}

void	free_data(t_data *data)
{
	free_scene(&data->scene);
	data->ui.htree.mlx_data = NULL;
	free_htree(&data->ui.htree);
	if (data->buffers.accu)
		free(data->buffers.accu);
}
