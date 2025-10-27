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

#include "calc.h"
#include "minirt.h"

int	parse_obj_type(const char *line, t_scene *scene, t_vec3 *pos, t_obj_vectors *vec);

int	parse_obj_file(int fd, t_scene *scene, t_vec3 *pos)
{
	char			*line;
	t_obj_vectors	vec;

	if (fd == -1)
		return (-1);
	vector_init(&vec.vertex, sizeof(t_vertex));
	vector_init(&vec.normal, sizeof(t_vec3));
	vector_init(&vec.uv, sizeof(t_vec2));
	vector_init(&vec.triangle, sizeof(t_triangle));
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (parse_obj_type(line, scene, pos, &vec) == -1)
		{
			free(vec.vertex.data);
			free(vec.normal.data);
			free(vec.uv.data);
			free(vec.triangle.data);
			return (-1);
		}
		line = get_next_line(fd);
	}
	free(vec.vertex.data);
	free(vec.normal.data);
	free(vec.uv.data);
	return (0);
}
