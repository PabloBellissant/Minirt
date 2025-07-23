/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 06:07:52 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/23 20:37:24 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include "libft.h"
#include "struct.h"
#include "parsing.h"
#include "vec3.h"


void	set_triangle_normal(t_triangle *triangle)
{
	t_vec3	edge1;
	t_vec3	edge2;

	vec3_sub(&triangle->p1.pos, &triangle->p0.pos, &edge1);
	vec3_sub(&triangle->p2.pos, &triangle->p0.pos, &edge2);
	vec3_cross(&edge1, &edge2, &triangle->normal);
	vec3_unit(&triangle->normal);
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
	return (return_val);
}
