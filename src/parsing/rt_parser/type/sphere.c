/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 02:44:47 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/17 02:44:48 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct.h"
#include "calc.h"

#define SPHERE_FORMAT " *sp +%f *, *%f *, *%f +%f +%8[255] *\
, *%8[255] *, *%8[255] *\n"

int	sphere(char *line, int line_num, t_scene *scene)
{
	t_sphere	*sphere;
	t_vec3		*pos;
	t_color		*color;
	t_object	*object;
	float		radius;

	object = create_object(scene, SPHERE);
	sphere = &object->sphere;
	pos = &sphere->pos;
	color = &sphere->color;
	ft_scan(line_num, SPHERE_FORMAT, line, &pos->x, &pos->y, &pos->z,
		&sphere->diameter, &color->r, &color->g, &color->b);
	radius = sphere->diameter / 2.0f;
	sphere->radius_squared = radius * radius;
	object->f = hit_sphere;
	return (0);
}
