/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 06:07:52 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/06 09:28:27 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include "libft.h"
#include "render.h"
#include "parsing.h"
#include "vectors.h"

int	init_phong(t_scene *scene)
{
	int	return_val;

	return_val = 0;
	scene->phong.l = ft_calloc(sizeof(t_vec3), scene->lights.num_elements);
	if (errno != 0)
	{
		return_val = -1;
		perror("Minirt");
	}
	scene->phong.r = ft_calloc(sizeof(t_vec3), scene->lights.num_elements);
	if (errno != 0)
	{
		return_val = -1;
		perror("Minirt");
	}
	scene->phong.d = ft_calloc(sizeof(t_vec3), scene->lights.num_elements);
	if (errno != 0)
	{
		return_val = -1;
		perror("Minirt");
	}
	return (return_val);
}

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
		errno = 0;
		line = get_next_line(fd);
		++line_num;
	}
	if (errno != 0)
	{
		return_val = -1;
		perror("Minirt");
	}
	else if (return_val == 0)
		return_val = init_phong(scene);
	return (return_val);
}
