/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 06:03:36 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/17 06:03:38 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct.h"

#define CYLINDER_FORMAT " *cy +%f *, *%f *, *%f +%f[-1,1] *, *%f[-1,1] *, *\
%f[-1,1] +%f +%f +%8[255] *, *%8[255] *, *%8[255] *\n"

int	cylinder(char *line, int line_num, t_scene *scene)
{
	t_cylinder	*cylinder;
	t_vec3		*pos;
	t_vec3		*rot;
	t_color		*color;
	t_object	*object;

	object = create_object(scene, CYLINDER);
	cylinder = &object->cylinder;
	pos = &cylinder->pos;
	color = &cylinder->color;
	rot = &cylinder->rot;
	ft_scan(line_num, CYLINDER_FORMAT, line, &pos->x, &pos->y, &pos->z,
		&rot->x, &rot->y, &rot->z, &cylinder->diameter, &cylinder->height,
		&color->r, &color->g, &color->b);
	return (0);
}
