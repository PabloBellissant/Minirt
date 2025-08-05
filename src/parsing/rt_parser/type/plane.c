/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 05:50:48 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 05:06:51 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "render.h"
#include "calc.h"
#include "vec3.h"

#define PLANE_FORMAT " *pl +%f *, *%f *, *%f +%f[-1,1] *, *%f[-1,1] *\
, *%f[-1,1] +%8[255] *, *%8[255] *, *%8[255] *\n"

int	plane(char *line, int line_num, t_scene *scene)
{
	t_plane		*plane;
	t_vec3		*pos;
	t_vec3		*norm;
	t_object	*object;
	t_color		color;

	object = create_object(scene, PLANE);
	plane = &object->plane;
	pos = &plane->pos;
	norm = &plane->normal;
	object->f = hit_plane;
	if (ft_scan(line_num, PLANE_FORMAT, line, &pos->x, &pos->y, &pos->z,
			&norm->x, &norm->y, &norm->z, &color.r, &color.g, &color.b))
		return (-1);
	get_real_ratio(&color, 1, &plane->rgb);
	return (0);
}
