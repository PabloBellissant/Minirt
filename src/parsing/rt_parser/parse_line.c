/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 22:00:39 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/31 16:35:21 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "parsing.h"

int	parse_line(t_scene *scene, char *line, int actual_line)
{
	t_object_type	type;
	static int		(*f[])(char *, int, t_scene *) = {ambient, camera, light, sphere, plane, cylinder, obj};

	if (line[0] == '#' || (line[0] == '/' && line[1] == '/') || line[0] == '\n')
		return (0);
	type = get_type(line, actual_line);
	if (type == UNDEFINED || check_float(type, actual_line) == -1)
		return (-1);
	return (f[type - 1](line, actual_line, scene));
}
