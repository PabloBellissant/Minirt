/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lpannel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:56:20 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 19:22:32 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			init_scene_list(t_data *data, t_hbranch *lpannel);
t_hbranch	*add_lpannel_switch(t_data *data, t_hbranch *lpannel);
int			init_edit_pannel(t_data *data, t_hbranch *lpannel);

static inline t_hbranch	*add_lpannel(t_data *data, t_hbranch *body)
{
	t_hbranch	*lpannel;

	lpannel = add_box(body, (t_radius){0}, (t_border){0});
	lpannel->size = vec2i(data->ui.lpannel_width, HEIGHT);
	lpannel->pos = vec2i(data->mlx->size.x, 0);
	lpannel->anchor = RT;
	lpannel->box.color = data->ui.htree.style.background;
	data->ui.lpannel_toggle = &lpannel->rendered;
	return (lpannel);
}

int	init_lpannel(t_data *data, t_hbranch *body)
{
	t_hbranch	*lpannel;
	t_hbranch	*lpannel_switch;

	lpannel = add_lpannel(data, body);
	if (!lpannel)
		return (1);
	if (init_scene_list(data, lpannel) != 0)
		return (1);
	if (init_edit_pannel(data, lpannel) != 0)
		return (1);
	lpannel_switch = add_lpannel_switch(data, lpannel);
	if (!lpannel_switch)
		return (1);
	if (!rebuild_inner_edit(NULL, data, data->ui.edit_pannel))
		return (1);
	return (0);
}
