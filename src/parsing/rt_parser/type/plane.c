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

static t_vec3	get_tangent(t_vec3 n);
static t_vec3	get_bitangent(t_vec3 n, t_vec3 tangent);

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
	object->mat_id = get_mat(mat_name, scene, &color);
	if (object->mat_id == -1)
		return (-1);
	object->f = hit_plane;
	object->plane.tangent = get_tangent(*norm);
	object->plane.bitangent = get_bitangent(*norm, object->plane.tangent);
	return (0);
}

static t_vec3	get_tangent(t_vec3 n)
{
	t_vec3 up;

	if (fabsf(n.y) > 0.999f)
		up = vec3(1, 0, 0);
	else
		up = vec3(0, 1, 0);
	return (vec3_normalize(vec3_cross(up, n)));
}

static t_vec3	get_bitangent(t_vec3 n, t_vec3 tangent)
{
	return (vec3_normalize(vec3_cross(n, tangent)));
}
