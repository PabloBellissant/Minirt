/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:23:40 by pabellis          #+#    #+#             */
/*   Updated: 2026/01/25 19:52:02 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "calc.h"
#include "vectors.h"
#include "rt_xcerrcal.h"

#define CYLINDER_FORMAT " *cy  *%f *, *%f *, *%f  *%f[-1,1] *, *%f[-1,1] *, *\
%f[-1,1]  *%f  *%f  *%8[255] *, *%8[255] *, *%8[255](  *%s) *\n\n"

int	cylinder(const char *line, int line_num, t_scene *scene)
{
	t_cylinder	*cylinder;
	t_rgb_int	color;
	t_object	*object;
	char		*mat_name;

	object = create_object(scene, CYLINDER);
	cylinder = &object->cylinder;
	if (ft_scan(line_num, CYLINDER_FORMAT, line,
			&cylinder->pos.x, &cylinder->pos.y, &cylinder->pos.z,
			&cylinder->rot.x, &cylinder->rot.y, &cylinder->rot.z,
			&cylinder->diameter, &cylinder->height,
			&color.r, &color.g, &color.b, &mat_name))
	{
		return (error(pack_err(RT_ID, RT_E_CYLINDER), FL, LN, FC));
	}
	object->mat_id = get_mat(mat_name, scene, &color);
	free(mat_name);
	if (object->mat_id == -1)
		return (-1);
	cylinder->radius = cylinder->diameter / 2;
	cylinder->rot = vec3_normalize(cylinder->rot);
	cylinder->rgb = rgb_itof(color);
	object->f = hit_cylinder;
	return (0);
}
