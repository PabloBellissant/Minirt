/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_handling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:56:30 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 11:45:07 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	clear_selected(t_data *data)
{
	size_t		i;
	t_object	**obj;

	i = 0;
	obj = data->ui.selection.selected.data;
	while (i < data->ui.selection.selected.num_elements)
	{
		clear_scene_select(data, obj[i]);
		i++;
	}
	free_vector(&data->ui.selection.selected);
	vector_init(&data->ui.selection.selected, sizeof(t_object *));
	destroy_edit_pannel(data);
}

/*
	Function that will add the object to the selected vector,
	will check if an associated scene entry exists and will color it
	correspondly (if first object or not)
	Will rebuild the selected editor if first object
*/
void	select_obj(t_data *data, t_object *obj)
{
	if (get_vector_index(&data->ui.selection.selected, &obj) != -1)
		return ;
	vector_add(&data->ui.selection.selected, &obj, 1);
	if (obj->type == TRIANGLE)
		return ;
	if (data->ui.selection.selected.num_elements == 1)
	{
		*data->ui.edit_mode = OBJ_EDIT_MODE;
		rebuild_inner_edit(NULL, data, data->ui.edit_pannel);
	}
	update_scene_select(data, obj);
}
