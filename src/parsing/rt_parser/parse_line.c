/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 22:00:39 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 05:14:00 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#define MUST_EXIST_COUNT 2

int	parse_line(t_scene *scene, const char *line, int actual_line)
{
	t_object_type		type;
	static int			(*f[])(const char *, int, t_scene *)
		= {ambient, camera, light, sphere, plane, cylinder, obj, tex, sky, mtl};

	if (line[0] == '#' || (line[0] == '/' && line[1] == '/') || line[0] == '\n')
		return (0);
	type = get_type(line);
	if (type == UNDEFINED || check_double(type) == -1)
		return (-1);
	return (f[type - 1](line, actual_line, scene));
}
