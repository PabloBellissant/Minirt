/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 22:00:39 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/05 05:18:17 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_line(t_scene *scene, const char *line, int actual_line)
{
	t_object_type		type;
	static int			(*f[])(const char *, int, t_scene *)
		= {ambient, camera, light, sphere, plane, obj, sky, mtl};

	if (line[0] == '#' || (line[0] == '/' && line[1] == '/') || line[0] == '\n')
		return (0);
	type = get_type(line);
	if (type == UNDEFINED || check_double(type) == -1)
		return (-1);
	return (f[type - 1](line, actual_line, scene));
}
