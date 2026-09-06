/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 06:07:52 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/20 17:30:57 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

int	rt_parser(int fd, t_scene *scene)
{
	char	*line;
	int		line_num;

	errno = 0;
	line_num = 1;
	line = get_next_line(fd);
	while (line)
	{
		if (parse_line(scene, line, line_num) != 0)
		{
			free(line);
			return (-1);
		}
		free(line);
		errno = 0;
		line = get_next_line(fd);
		++line_num;
	}
	if (errno != 0)
		return (-1);
	if (scene->skybox_tex == -1)
		scene->skybox_tex
			= create_color_texture(&scene->texture, &(t_rgb_int){{0, 0, 0}});
	return (scene->skybox_tex == -1);
}
