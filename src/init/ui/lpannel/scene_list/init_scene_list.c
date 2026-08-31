/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:02:39 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 19:28:00 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline t_hbranch	*add_scene_list_box(t_data *data, t_hbranch *lpannel)
{
	t_hbranch		*box;

	box = add_box(lpannel, (t_radius){.style = FULL_PX, .full = 7},
			(t_border){.style = SOLID, .size = 1});
	if (!box)
		return (NULL);
	box->pos = vec2i(lpannel->pos.x - 4, lpannel->pos.y + 2);
	box->anchor = RT;
	box->size = vec2i(lpannel->size.x + 1, data->ui.scene_height);
	box->size = vec2i_sub_scalar(box->size, 6);
	return (box);
}

static inline t_hbranch	*add_scene_list_scrollbox(t_hbranch *box)
{
	t_hbranch		*scene_list;

	scene_list = add_scrollbox(box);
	if (!scene_list)
		return (NULL);
	scene_list->pos = vec2i(box->pos.x + 1 - box->box.radius.full / 2,
			box->pos.y + box->box.radius.full / 2);
	scene_list->anchor = RT;
	scene_list->scrollbox._current_pos = 0;
	scene_list->size = vec2i_sub_scalar(box->size, box->box.radius.full - 2);
	scene_list->size.x += 1;
	scene_list->scrollbox.inside->size.x = scene_list->size.x;
	return (scene_list);
}

int	init_scene_list(t_data *data, t_hbranch *lpannel)
{
	t_hbranch		*scene_list;
	t_hbranch		*box;
	size_t			num_entries;

	box = add_scene_list_box(data, lpannel);
	if (!box)
		return (1);
	scene_list = add_scene_list_scrollbox(box);
	if (!scene_list)
		return (1);
	num_entries = 0;
	populate_scene_list(data, scene_list->scrollbox.inside, &num_entries);
	scene_list->scrollbox.inside->size.y = ENTRY_HEIGHT * num_entries;
	return (0);
}
