/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_scene_entry.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:09:39 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 19:27:23 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	select_entry(t_hbranch *hbranch, void *arg1, void *arg2);

static inline t_hbranch	*add_scene_entry_label(t_hbranch *entry,
							char *name)
{
	t_hbranch	*entry_label;

	entry_label = add_textbox(entry, (t_text){.font_size = 2,
			.fg = (t_rgba_int){.rgba = WHITE}}, CENTER_ALIGN, NO_WRAPPING);
	if (!entry_label)
		return (NULL);
	entry_label->textbox.vert_align = MIDDLE_ALIGN;
	entry_label->anchor = LT;
	entry_label->size = entry->size;
	entry_label->x_pos_operation = copy;
	entry_label->y_pos_operation = copy;
	ft_strlcpy(entry_label->textbox.content, name, MAX_CHARS);
	return (entry_label);
}

t_hbranch	*add_scene_entry(t_hbranch *scene_list, char *name,
				t_object *obj, t_data *data)
{
	t_hbranch	*entry;
	t_hbranch	*entry_label;

	entry = add_button(scene_list, (t_radius){0}, (t_border){0});
	if (!entry)
		return (NULL);
	entry->anchor = LT;
	entry->size = vec2i(scene_list->size.x, ENTRY_HEIGHT);
	entry->button.action2 = select_entry;
	entry->button.args2[0] = obj;
	entry->button.args2[1] = data;
	entry_label = add_scene_entry_label(entry, name);
	if (!entry_label)
		return (NULL);
	if (scene_list->childs->num_elements <= MAX_SCENE_ENTRIES)
		data->ui.scene_entries[scene_list->childs->num_elements - 1]
			= (t_scene_entry){.obj = obj, .entry = entry};
	return (entry);
}
