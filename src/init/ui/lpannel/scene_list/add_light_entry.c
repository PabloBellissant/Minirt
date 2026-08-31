/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_light_entry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:16:11 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 19:41:16 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define LIGHT_LABEL "Light %d"

static inline t_hbranch	*add_light_entry(t_block_util bl, t_light *light,
							size_t i, size_t *num_entries)
{
	char		name[MAX_CHARS];
	t_hbranch	*entry;

	(void)light;
	strf(name, MAX_CHARS, LIGHT_LABEL, (int)i);
	entry = add_scene_entry(bl.comp, name, NULL, bl.data);
	if (!entry)
		return (NULL);
	entry->pos.y += *num_entries * ENTRY_HEIGHT;
	if (*num_entries % 2)
		entry->box.color.a = 120;
	else
		entry->box.color.a = 180;
	(*num_entries)++;
	return (entry);
}

int	init_light_entries(t_hbranch *scene_list, size_t *num_entries,
		t_data *data)
{
	t_vector		lights_vec;
	t_light			*lights;
	t_hbranch		*entry;
	size_t			i;
	t_block_util	bl;

	i = 0;
	lights_vec = data->scene.light;
	lights = lights_vec.data;
	while ((i < lights_vec.num_elements) && (*num_entries < MAX_SCENE_ENTRIES))
	{
		bl = (t_block_util){.comp = scene_list, .data = data};
		entry = add_light_entry(bl, lights + i, i, num_entries);
		if (!entry)
			return (1);
		i++;
	}
	return (0);
}
