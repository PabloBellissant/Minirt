/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 05:50:48 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/14 02:25:55 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "calc.h"
#include "vectors.h"
#include "rt_xcerrcal.h"
#include "parsing.h"

#define PLANE_FORMAT " *pl  *%f *, *%f *, *%f  *%f[-1,1] *, *%f[-1,1] *\
, *%f[-1,1]  *%8[255] *, *%8[255] *, *%8[255](  *%s) *\n"

int	plane(const char *line, int line_num, t_scene *scene)
{
	t_vec3		*pos;
	t_vec3		*norm;
	t_object	*object;
	t_rgb_int	color;
	char		*mat_name;

	object = create_object(scene, PLANE);
	pos = &object->plane.pos;
	norm = &object->plane.normal;
	mat_name = NULL;
	if (ft_scan(line_num, PLANE_FORMAT, line, &pos->x, &pos->y, &pos->z,
			&norm->x, &norm->y, &norm->z, &color.r, &color.g, &color.b,
					&mat_name))
	{
		return (error(pack_err(RT_ID, RT_E_PLANE), FL, LN, FC));
	}
	if (*mat_name)
		object->mat = *get_mat(mat_name, &scene->mat); // a secu
	else
		object->mat.kd = rgb_itof(color);
	object->f = hit_plane;
	return (0);
}
