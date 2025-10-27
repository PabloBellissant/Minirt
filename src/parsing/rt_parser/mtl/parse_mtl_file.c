/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mtl_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 04:15:27 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/21 04:15:29 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	parse_mtl_file(int fd, t_scene *scene)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (parse_mtl_type(line, scene) == -1)
			return (-1);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
