/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_scene_entries.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:26:16 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/18 19:48:38 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline t_hbranch	*find_select_entry(t_data *data, t_object *obj)
{
	size_t			i;
	t_scene_entry	*scene_entries;

	i = 0;
	scene_entries = data->ui.scene_entries;
	while (i < MAX_SCENE_ENTRIES)
	{
		if (scene_entries[i].obj == obj)
			return (scene_entries[i].entry);
		i++;
	}
	return (NULL);
}

static inline t_rgba_int	*get_color_text_entry(t_data *data, t_object *obj)
{
	t_hbranch	*entry;
	t_hbranch	*textbox;

	entry = find_select_entry(data, obj);
	if (!entry)
		return (NULL);
	textbox = get_hbranch_child_idx(entry, 0);
	if (!textbox)
		return (NULL);
	return (&textbox->textbox.fg);
}

/*
	Sets scene entry label to orange or dark orange depending on
	current selected
*/
void	update_scene_select(t_data *data, t_object *obj)
{
	t_rgba_int	*label_col;

	label_col = get_color_text_entry(data, obj);
	if (!label_col)
		return ;
	if (data->ui.selection.selected.num_elements == 1)
		*label_col = drgba_int(FSELECT_COLOR);
	else
		*label_col = drgba_int(SELECT_COLOR);
	label_col->a = 255;
}

/*
	Sets scene entry label to white
*/
void	clear_scene_select(t_data *data, t_object *obj)
{
	t_rgba_int	*label_col;

	label_col = get_color_text_entry(data, obj);
	if (!label_col)
		return ;
	*label_col = drgba_int(WHITE);
	label_col->a = 255;
}
