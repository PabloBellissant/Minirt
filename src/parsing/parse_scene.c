/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 01:03:48 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 04:50:37 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "bvh.h"
#include <fcntl.h>

#include "render.h"

int	parse_scene(char *file_name, t_scene *scene)
{
	int	fd;

	if (ft_strrncmp(file_name, ".rt", 3) != 0)
		return (-1);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	if (rt_parser(fd, scene) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	scene->bvh.bvh_mode = 1;
	if (load_bvh(scene->bvh.bvh_mode, scene) == -1)
		return (-1);
	if (fill_by_type(scene) == -1)
		return (-1); //free
	return (0);
}
