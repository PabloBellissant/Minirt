/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 02:44:47 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/07 09:47:21 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "calc.h"
#include "vectors.h"

#define SPHERE_FORMAT " *sp  *%f *, *%f *, *%f  *%f  *%8[255] *\
, *%8[255] *, *%8[255](  *%s) *\n"

int	sphere(const char *line, int line_num, t_scene *scene)
{
	t_sphere	*sphere;
	t_vec3		*pos;
	t_rgb_int	color;
	t_object	*object;
	char		*texture_name;

	object = create_object(scene, SPHERE);
	sphere = &object->sphere;
	pos = &sphere->pos;
	if (ft_scan(line_num, SPHERE_FORMAT, line, &pos->x, &pos->y, &pos->z,
			&sphere->diameter, &color.r, &color.g, &color.b, &texture_name))
		return (-1);
	if (*texture_name != 0)
	{
		object->texture = get_texture(scene, texture_name);
		if (!object->texture)
		{
			ft_dprintf(2, "Error\nCannot find texture '%s', line : '%d'\n", texture_name, line_num);
			return (-1);
		}
	}
	sphere->radius_squared = (sphere->diameter / 2.0f)
		* (sphere->diameter / 2.0f);
	object->f = hit_sphere;
	sphere->rgb = rgb_itof(color);
	return (0);
}
