/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_kd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 05:14:38 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/21 05:14:50 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "parsing.h"

#define MAP_KD_FORMAT " *map_Kd  *%s *\n"

int	map_kd(const char *line, t_scene *scene)
{
	t_mat	*mat;
	char	*name;

	mat = get_last_vector_value(&scene->mat);
	if (ft_scan(0, MAP_KD_FORMAT, line, &name))
		return (-1);
	mat->map_kd = create_texture(scene, name);
	if (!mat->map_kd)
		return (-1);
	return (0);
}
