/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 23:57:59 by pabellis          #+#    #+#             */
/*   Updated: 2025/11/23 23:58:01 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "parsing.h"

#define MAP_D_FORMAT " *map_d  *%s *\n"

int	map_d(const char *line, t_scene *scene)
{
	t_mat		*mat;
	char		*name;

	mat = get_last_vector_value(&scene->mat);
	if (ft_scan(0, MAP_D_FORMAT, line, &name))
		return (-1);
	if (!parse_texture(scene, name))
		return (-1);
	mat->opacity_id.index = (int) scene->texture.num_elements - 1;
	return (0);
}
