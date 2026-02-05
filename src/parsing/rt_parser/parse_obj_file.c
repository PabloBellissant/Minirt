/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 02:28:59 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/02 02:29:02 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			parse_obj_type(const char *line, t_scene *scene,
				t_obj_attribute *attr, t_obj_vectors *vec);
static void	init_vectors(t_obj_vectors *vec, t_scene *scene);

int	parse_obj_file(int fd, t_scene *scene, t_obj_attribute *attr)
{
	char			*line;
	t_obj_vectors	vec;

	if (fd == -1)
		return (-1);
	init_vectors(&vec, scene);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (parse_obj_type(line, scene, attr, &vec) == -1)
		{
			free(vec.vertex.data);
			free(vec.normal.data);
			free(vec.uv.data);
			free(line);
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(vec.vertex.data);
	free(vec.normal.data);
	free(vec.uv.data);
	return (0);
}

static void	init_vectors(t_obj_vectors *vec, t_scene *scene)
{
	vector_init(&vec->vertex, sizeof(t_vertex));
	vector_init(&vec->normal, sizeof(t_vec3));
	vector_init(&vec->uv, sizeof(t_vec2));
	vec->tex = &scene->texture;
	vec->mat = &scene->mat;
}
