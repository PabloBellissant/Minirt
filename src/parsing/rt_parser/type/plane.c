/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 05:50:48 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/17 05:50:49 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct.h"

#define PLANE_FORMAT " *pl +%f *, *%f *, *%f +%f[-1,1] *, *%f[-1,1] *\
, *%f[-1,1] +%8[255] *, *%8[255] *, *%8[255] *\n"

int	plane(char *line, int line_num, t_scene *scene)
{
	t_plane		*plane;
	t_vec3		*pos;
	t_vec3		*norm;
	t_color		*color;
	t_object	*object;

	object = create_object(scene, PLANE);
	plane = &object->plane;
	pos = &plane->pos;
	color = &plane->color;
	norm = &plane->normal;
	ft_scan(line_num, PLANE_FORMAT, line, &pos->x, &pos->y, &pos->z, &norm->x,
		&norm->y, &norm->z, &color->r, &color->g, &color->b);
	return (0);
}
