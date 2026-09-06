/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj_entry.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:21:39 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 20:04:43 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define OBJ_LABEL "%s %d"

static inline t_hbranch	*add_obj_entry(t_block_util bl, t_object *obj,
							size_t i, size_t *num_entries)
{
	char		name[MAX_CHARS];
	t_hbranch	*entry;

	if (get_obj_label(obj, name))
	{
		strf(name, MAX_CHARS, OBJ_LABEL, name, (int)i);
		entry = add_scene_entry(bl.comp, name, obj, bl.data);
		entry->pos.y += *num_entries * ENTRY_HEIGHT;
		if (*num_entries % 2)
			entry->box.color.a = 120;
		else
			entry->box.color.a = 180;
		(*num_entries)++;
	}
	else
		return (bl.comp);
	return (entry);
}

int	init_obj_entries(t_hbranch *scene_list, size_t *num_entries, t_data *data)
{
	t_vector		objects_vec;
	t_object		*objects;
	t_hbranch		*entry;
	size_t			i;
	t_block_util	bl;

	i = 0;
	objects_vec = data->scene.objects;
	objects = objects_vec.data;
	while ((i < objects_vec.num_elements) && (*num_entries < MAX_SCENE_ENTRIES))
	{
		bl = (t_block_util){.comp = scene_list, .data = data};
		entry = add_obj_entry(bl, objects + i, i, num_entries);
		if (!entry)
			return (1);
		i++;
	}
	return (0);
}
