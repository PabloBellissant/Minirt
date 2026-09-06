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
#include "object.h"
#include "rt_xcerrcal.h"
#include "parsing.h"
#include "render.h"

#define PLANE_FORMAT " *pl  *%f *, *%f *, *%f  *%f[-1,1] *, *%f[-1,1] *\
, *%f[-1,1]  *%8[255] *, *%8[255] *, *%8[255](  *%s %f) *\n"

int	plane(const char *line, int line_num, t_scene *scene)
{
	t_vec3		*pos;
	t_vec3		*norm;
	t_object	*object;
	t_rgb_int	color;
	char		*mat_name;

	object = create_object(scene, PLANE);
	if (object == NULL)
		return (-1);
	pos = &object->plane.pos;
	norm = &object->plane.normal;
	mat_name = NULL;
	if (ft_scan(line_num, PLANE_FORMAT, line, &pos->x, &pos->y, &pos->z,
			&norm->x, &norm->y, &norm->z, &color.r, &color.g, &color.b,
			&mat_name, &object->plane.texture_scaling))
	{
		free(mat_name);
		return (error(pack_err(RT_ID, RT_E_PLANE), FL, LN, FC));
	}
	object->mat_id = get_mat(mat_name, scene, &color);
	object->name = mat_name;
	object->plane.tangent = get_tangent(*norm);
	object->plane.bitangent = get_bitangent(*norm, object->plane.tangent);
	scene->plane_count++;
	return (object->mat_id == -1);
}
