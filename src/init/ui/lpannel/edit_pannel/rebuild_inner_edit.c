/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rebuild_inner_edit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 08:57:28 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 19:42:39 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hbranch	*add_inner_edit(t_hbranch *edit_pannel);
t_hbranch	*populate_inner_edit(t_data *data, t_hbranch *inner_edit,
				int *y_size);

t_hbranch	*rebuild_inner_edit(t_hbranch *v, t_data *data,
				t_hbranch *edit_pannel)
{
	t_hbranch	*inner_edit;
	int			y_size;

	(void)v;
	destroy_edit_pannel(data);
	y_size = 0;
	inner_edit = add_inner_edit(edit_pannel);
	if (!inner_edit)
		return (NULL);
	data->ui.inner_edit = inner_edit;
	populate_inner_edit(data, inner_edit->scrollbox.inside, &y_size);
	if (y_size > inner_edit->scrollbox.inside->size.y)
		inner_edit->scrollbox.inside->size.y = y_size;
	else
		inner_edit->scrollbox.inside->size.y = inner_edit->size.y;
	precompute_hbranch(inner_edit->parent);
	return (inner_edit);
}
