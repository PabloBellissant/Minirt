/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_edit_pannel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:10:20 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 10:39:58 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline t_hbranch	*add_edit_pannel(t_data *data, t_hbranch *lpannel)
{
	t_hbranch	*edit_pannel;

	edit_pannel = add_box(lpannel, (t_radius){.style = FULL_PX, .full = 7},
			(t_border){.style = SOLID, .size = 1});
	if (!edit_pannel)
		return (NULL);
	edit_pannel->pos = vec2i(lpannel->pos.x - 4, lpannel->pos.y + 2
			+ data->ui.scene_height + data->ui.lpannel_switch_height);
	edit_pannel->anchor = RT;
	edit_pannel->size = vec2i(lpannel->size.x, data->ui.lpannel_edit_height);
	edit_pannel->size = vec2i_sub_scalar(edit_pannel->size, 6);
	return (edit_pannel);
}

int	init_edit_pannel(t_data *data, t_hbranch *lpannel)
{
	data->ui.inner_edit = NULL;
	data->ui.edit_pannel = add_edit_pannel(data, lpannel);
	if (!data->ui.edit_pannel)
		return (1);
	return (0);
}
