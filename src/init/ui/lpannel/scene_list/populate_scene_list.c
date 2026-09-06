/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_scene_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:07:45 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 19:29:38 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline t_hbranch	*add_max_msg_entry(t_hbranch *scene_list,
							size_t *num_entries, t_data *data)
{
	char		name[MAX_CHARS];
	t_hbranch	*entry;

	strf(name, MAX_CHARS, MAX_SCENE_ENTRIES_MSG, MAX_SCENE_ENTRIES);
	entry = add_scene_entry(scene_list, name, NULL, data);
	if (*num_entries % 2)
		entry->box.color.a = 120;
	else
		entry->box.color.a = 180;
	entry->pos.y += *num_entries * ENTRY_HEIGHT;
	(*num_entries)++;
	if (DEBUG)
		printf(MAX_SCENE_LOG, MAX_SCENE_ENTRIES);
	return (entry);
}

t_hbranch	*add_cam_entry(t_hbranch *scene_list, size_t *num_entries,
							t_data *data);
int			init_light_entries(t_hbranch *scene_list, size_t *num_entries,
							t_data *data);
int			init_obj_entries(t_hbranch *scene_list, size_t *num_entries,
							t_data *data);

int	populate_scene_list(t_data *data, t_hbranch *scene_list,
		size_t *num_entries)
{
	if (!add_cam_entry(scene_list, num_entries, data))
		return (1);
	if (init_light_entries(scene_list, num_entries, data) != 0)
		return (1);
	if (init_obj_entries(scene_list, num_entries, data) != 0)
		return (1);
	if (*num_entries == MAX_SCENE_ENTRIES)
	{
		if (!add_max_msg_entry(scene_list, num_entries, data))
			return (1);
	}
	return (0);
}
