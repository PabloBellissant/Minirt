/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 06:07:52 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/21 20:15:30 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include "libft.h"
#include "render.h"
#include "parsing.h"
#include "vectors.h"

int	rt_parser(int fd, t_scene *scene)
{
	char	*line;
	int		return_val;
	int		line_num;

	errno = 0;
	return_val = 0;
	line_num = 1;
	line = get_next_line(fd);
	while (line)
	{
		if (parse_line(scene, line, line_num) != 0)
			return_val = -1;
		free(line);
		if (return_val == -1)
			return (-1);
		errno = 0;
		line = get_next_line(fd);
		++line_num;
	}
	if (errno != 0)
		return (-1);
	if (scene->skybox_tex == -1)
		scene->skybox_tex = create_color_texture(&scene->texture, &(t_rgb_int){{0, 100, 255}});
	if (scene->skybox_tex == -1)
		return (-1);
	return (return_val);
}
