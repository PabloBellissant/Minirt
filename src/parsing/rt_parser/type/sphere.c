/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 02:44:47 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/14 06:42:52 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "calc.h"
#include "vectors.h"
#include "rt_xcerrcal.h"

#define SPHERE_FORMAT " *sp  *%f *, *%f *, *%f  *%f  *%8[255] *\
, *%8[255] *, *%8[255](  *%s) *\n"

int	sphere(const char *line, int line_num, t_scene *scene)
{
	t_vec3		*pos;
	t_rgb_int	color;
	t_object	*object;
	char		*mat_name;

	object = create_object(scene, SPHERE);
	pos = &object->sphere.pos;
	if (ft_scan(line_num, SPHERE_FORMAT, line, &pos->x, &pos->y, &pos->z,
			&object->sphere.diameter, &color.r, &color.g, &color.b,
			&mat_name))
	{
		return (error(pack_err(RT_ID, RT_E_SPHERE), FL, LN, FC));
	}
	object->sphere.radius_squared = (object->sphere.diameter / 2.f)
		* (object->sphere.diameter / 2.f);
	if (*mat_name)
		object->mat = *get_mat(mat_name, &scene->mat);
	else
		object->mat.kd = rgb_itof(color);
	object->f = hit_sphere;
	return (0);
}
