/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj_label.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:49:20 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/18 18:49:22 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define EDITABLE_OBJS 3

bool	get_obj_label(t_object *obj, char *name)
{
	const t_object_type	types[EDITABLE_OBJS] = {SPHERE, PLANE, MESH};
	const char			*type_name[EDITABLE_OBJS] = {"Sphere", "Plane", "Mesh"};
	size_t				i;

	i = 0;
	while (i < EDITABLE_OBJS)
	{
		if (obj->type == types[i])
		{
			strf(name, MAX_CHARS, "%s", type_name[i]);
			return (true);
		}
		i++;
	}
	return (false);
}
