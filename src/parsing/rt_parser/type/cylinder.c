/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:23:40 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/08 03:36:12 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "calc.h"
#include "vectors.h"

#define CYLINDER_FORMAT " *cy  *%f *, *%f *, *%f  *%f[-1,1] *, *%f[-1,1] *, *\
%f[-1,1]  *%f  *%f  *%8[255] *, *%8[255] *, *%8[255] *\n"

int	cylinder(const char *line, int line_num, t_scene *scene)
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
	if (ft_scan(line_num, CYLINDER_FORMAT, line, &pos->x, &pos->y, &pos->z,
			&rot->x, &rot->y, &rot->z, &cylinder->radius, &cylinder->height,
			&color.r, &color.g, &color.b))
		return (-1);
	cylinder->radius /= 2;
	cylinder->rot = vec3_normalize(cylinder->rot);
	cylinder->rgb = rgb_itof(color);
	object->f = hit_cylinder;
	return (0);
}
