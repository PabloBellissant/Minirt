/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 06:07:52 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/11 06:07:54 by pabellis         ###   ########.fr       */
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
	// t_object	*object = create_object(scene, TRIANGLE);
	// t_triangle	*triangle;
	//
	// triangle = &object->triangle;
	// triangle->color = (t_color) {{0,255,255,0}};
	// triangle->p0.pos.x = 1.5f;
	// triangle->p0.pos.y = -1;
	// triangle->p0.pos.z = -5;
	// triangle->p1.pos.x = 2.2f;
	// triangle->p1.pos.y = 2.5f;
	// triangle->p1.pos.z = -5;
	// triangle->p2.pos.x = -2.f;
	// triangle->p2.pos.y = -1.5f;
	// triangle->p2.pos.z = -5;
	// dprintf(2, "%f %f %f\n", ((t_object *)scene->objects.data)[0].sphere.pos.x, ((t_object *)scene->objects.data)[0].sphere.pos.y, ((t_object *)scene->objects.data)[0].sphere.pos.z);
	// set_triangle_normal(triangle);
	return (return_val);
}
