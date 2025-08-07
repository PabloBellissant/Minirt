/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 06:03:36 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/06 09:53:00 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "render.h"
#include "calc.h"
#include "vectors.h"

#define CYLINDER_FORMAT " *cy  *%f *, *%f *, *%f  *%f[-1,1] *, *%f[-1,1] *, *\
%f[-1,1]  *%f  *%f  *%8[255] *, *%8[255] *, *%8[255] *\n"

int	cylinder(char *line, int line_num, t_scene *scene)
{
	t_cylinder	*cylinder;
	t_vec3		*pos;
	t_vec3		*rot;
	t_rgb_int	color;
	t_object	*object;

	object = create_object(scene, CYLINDER);
	cylinder = &object->cylinder;
	pos = &cylinder->pos;
	rot = &cylinder->rot;
	object->f = hit_cylinder;
	if (ft_scan(line_num, CYLINDER_FORMAT, line, &pos->x, &pos->y, &pos->z,
			&rot->x, &rot->y, &rot->z, &cylinder->diameter, &cylinder->height,
			&color.r, &color.g, &color.b))
		return (-1);
	cylinder->rgb = rgb_itof(color);
	return (0);
}
