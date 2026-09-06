/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_obj_edit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:25:56 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 20:33:27 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	populate_obj_geometry(t_data *data, t_hbranch *obj_edit, int *y_size,
		t_object *obj);
int	populate_mat_edit(t_data *data, t_hbranch *obj_edit, int *y_size,
		t_mat *mat);

t_hbranch	*populate_obj_edit(t_data *data, t_hbranch *obj_edit, int *y_size,
				t_object *obj)
{
	char		title[MAX_CHARS];
	t_hbranch	*textbox;
	t_mat		*mat;

	if (obj)
	{
		get_obj_label(obj, title);
		textbox = add_edit_pannel_title(obj_edit, y_size, title);
	}
	else
		textbox = add_edit_pannel_title(obj_edit, y_size, "No obj");
	if (!textbox)
		return (NULL);
	if (!obj)
		return (textbox);
	if (populate_obj_geometry(data, obj_edit, y_size, obj) != 0)
		return (NULL);
	mat = get_vector_value(&data->scene.mat, obj->mat_id);
	if (mat)
	{
		if (populate_mat_edit(data, obj_edit, y_size, mat) != 0)
			return (NULL);
	}
	return (textbox);
}
