/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 00:40:54 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/14 08:12:41 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "render.h"
#include "vectors.h"
#include "rt_xcerrcal.h"

#define LIGHT_FORMAT " *L  *%f *, *%f *, *%f  *%f[1]  *%8[255] *\
, *%8[255] *, *%8[255] *\n"

static t_object	*create_light(t_scene *scene, t_object_type type)
{
	t_object	object;

	if (scene->lights.max_elements == 0)
		vector_init(&scene->lights, sizeof(t_object));
	ft_bzero(&object, sizeof(t_object));
	object.type = type;
	if (vector_add(&scene->lights, &object, 1) == -1)
		return (NULL);
	return (get_vector_value(&scene->lights, scene->lights.num_elements - 1));
}

int	light(const char *line, int line_num, t_scene *scene)
{
	t_light		*light;
	t_vec3		*pos;
	t_rgb_int	color;
	t_object	*object;

	object = create_light(scene, LIGHT);
	light = &object->light;
	pos = &light->pos;
	if (ft_scan(line_num, LIGHT_FORMAT, line, &pos->x, &pos->y, &pos->z,
			&light->brightness, &color.r, &color.g, &color.b))
	{
		return (error(pack_err(RT_ID, RT_E_LIGHT), FL, LN, FC));
	}
	light->rgb = get_real_ratio(color, light->brightness);
	return (0);
}
