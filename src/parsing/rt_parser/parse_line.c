/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 22:00:39 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/11 22:00:40 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_line(t_scene *scene, char *line, int actual_line)
{
	t_object_type	type;

	if (line[0] == '#' || (line[0] == '/' && line[1] == '/') || line[0] == '\n')
		return (0);
	type = get_type(line, actual_line);
	if (check_double(type, actual_line) == -1)
		return (-1);
	(void) scene;
	return (0);
}
