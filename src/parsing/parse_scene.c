/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 01:03:48 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/31 20:37:17 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct.h"
#include "bvh.h"

int	parse_scene(char *file_name, t_scene *scene)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (!fd)
		return (-1);
	if (rt_parser(fd, scene) == -1)
		return (-1);
	if (create_bvh(scene) == -1)
		return (-1);
	return (0);
}
