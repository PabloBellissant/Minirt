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
	t_sphere	*sp;
	t_vec3		*pos;
	t_rgb_int	color;
	t_object	*object;
	char		*texture_name;

	object = create_object(scene, SPHERE);
	sp = &object->sphere;
	pos = &sp->pos;
	if (ft_scan(line_num, SPHERE_FORMAT, line, &pos->x, &pos->y, &pos->z,
			&sp->diameter, &color.r, &color.g, &color.b, &texture_name))
		return (error(pack_err(RT_ID, RT_E_SPHERE), FL, LN, FC));
	if (*texture_name != 0)
	{
		object->texture = get_texture(scene, texture_name);
		if (!object->texture)
		{
			register_complex_err_msg(RT_E_MSG_NO_TEX, texture_name);
			return (error(pack_err(RT_ID, RT_E_NO_TEX), FL, LN, FC));
		}
	}
	sp->radius_squared = (sp->diameter / 2.f) * (sp->diameter / 2.f);
	object->f = hit_sphere;
	sp->rgb = rgb_itof(color);
	return (0);
}
