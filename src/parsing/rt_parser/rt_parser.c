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
#include <math.h>
#include "libft.h"
#include "struct.h"
#include "init.h"
#include "parsing.h"
#include "vec3.h"

// #define X 0.525731112119133606f
// #define Z 0.850650808352039932f
//
// void	create_icosphere(t_scene *scene, t_vec3 center)
// {
// 	static const t_vec3 base_vertices[12] = {
// 		{-X, 0, Z}, {X, 0, Z}, {-X, 0, -Z}, {X, 0, -Z},
// 		{0, Z, X}, {0, Z, -X}, {0, -Z, X}, {0, -Z, -X},
// 		{Z, X, 0}, {-Z, X, 0}, {Z, -X, 0}, {-Z, -X, 0}
// 	};
// 	static const int faces[20][3] = {
// 		{0, 4, 1}, {0, 9, 4}, {9, 5, 4}, {4, 5, 8}, {4, 8, 1},
// 		{8, 10, 1}, {8, 3, 10}, {5, 3, 8}, {5, 2, 3}, {2, 7, 3},
// 		{7, 10, 3}, {7, 6, 10}, {7, 11, 6}, {11, 0, 6}, {0, 1, 6},
// 		{6, 1, 10}, {9, 0, 11}, {9, 11, 2}, {9, 2, 5}, {7, 2, 11}
// 	};
// 	t_vec3	vertices[12];
// 	int		i;
// 	float	scale;
// 	t_object *object;
// 	t_triangle *triangle;
//
// 	scale = 1.0f; // rayon de la sphère unité
// 	i = 0;
// 	while (i < 12)
// 	{
// 		float	len = sqrtf(
// 			base_vertices[i].x * base_vertices[i].x +
// 			base_vertices[i].y * base_vertices[i].y +
// 			base_vertices[i].z * base_vertices[i].z
// 		);
// 		vertices[i].x = (base_vertices[i].x / len) * scale + center.x;
// 		vertices[i].y = (base_vertices[i].y / len) * scale + center.y;
// 		vertices[i].z = (base_vertices[i].z / len) * scale + center.z;
// 		i++;
// 	}
// 	i = 0;
// 	while (i < 20)
// 	{
// 		object = create_object(scene, TRIANGLE);
// 		triangle = &object->triangle;
// 		triangle->color = (t_color){{.r = 255, .g = 255, .b = 0}};
// 		triangle->p0.pos = vertices[faces[i][0]];
// 		triangle->p1.pos = vertices[faces[i][1]];
// 		triangle->p2.pos = vertices[faces[i][2]];
//
// 		i++;
// 	}
// }

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
