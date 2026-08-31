/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_inner_edit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:03:30 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 14:19:46 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hbranch	*populate_render_edit(t_data *data, t_hbranch *render_edit,
				int *y_size);
t_hbranch	*populate_obj_edit(t_data *data, t_hbranch *obj_edit,
				int *y_size, t_object *obj);

t_hbranch	*populate_inner_edit(t_data *data, t_hbranch *inner_edit,
				int *y_size)
{
	t_hbranch	*ret;
	t_object	**obj;

	ret = NULL;
	if (data->ui.edit_mode)
	{
		if (*data->ui.edit_mode == OBJ_EDIT_MODE)
		{
			obj = get_vector_value(&data->ui.selection.selected, 0);
			if (obj)
				ret = populate_obj_edit(data, inner_edit, y_size, *obj);
			else
				ret = populate_obj_edit(data, inner_edit, y_size, NULL);
		}
		else if (*data->ui.edit_mode == RENDER_EDIT_MODE)
			ret = populate_render_edit(data, inner_edit, y_size);
	}
	else
		return (inner_edit);
	return (ret);
}
