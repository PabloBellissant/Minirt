/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 00:40:54 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/17 00:40:56 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct.h"

#define LIGHT_FORMAT " *L +%f *, *%f *, *%f +%f[1] +%8[255] *\
, *%8[255] *, *%8[255] *\n"

int	light(char *line, int line_num, t_scene *scene)
{
	t_light		*light;
	t_vec3		*pos;
	t_color		*color;
	t_object	*object;

	object = create_object(scene, LIGHT);
	light = &object->light;
	pos = &light->pos;
	color = &light->color;
	ft_scan(line_num, LIGHT_FORMAT, line, &pos->x, &pos->y, &pos->z,
		&light->brightness, &color->r, &color->g, &color->b);
	return (0);
}
