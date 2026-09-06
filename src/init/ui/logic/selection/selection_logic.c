/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_logic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:36:45 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 11:45:17 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rearrange_order(t_vec2i *mouse_pos);
bool	is_click_inside(t_vec2i pos, t_vec2i screen_size,
			t_hbranch *ondisplay_ui);

static inline bool	is_obj_inside(t_vec2i *select_zone,
						t_vec2i obj_screen_pos)
{
	return ((select_zone[START].x < obj_screen_pos.x)
		&& (select_zone[START].y < obj_screen_pos.y)
		&& (select_zone[END].x > obj_screen_pos.x)
		&& (select_zone[END].y > obj_screen_pos.y));
}

static inline void	find_selected_objs(t_vec2i *select_zone, t_data *data)
{
	size_t		i;
	t_object	*o;
	t_vec2i		obj_screen_pos;

	i = 0;
	o = data->scene.objects.data;
	while (i < data->scene.objects.num_elements)
	{
		obj_screen_pos = project_point(&(o[i].centroid),
				&data->scene.camera, &data->mlx->img);
		if (is_obj_inside(select_zone, obj_screen_pos))
			select_obj(data, o + i);
		i++;
	}
	update_info_display(data);
}

void	select_zone(t_vec2i pos, t_maction action,
			t_data *data, t_mlx *mlx_data)
{
	t_vec2i	*mouse_pos;

	mouse_pos = data->ui.selection.mouse_pos;
	rearrange_order(mouse_pos);
	if (mlx_data->mouse_input.focus)
		return ;
	if ((action == MPRESS) && is_click_inside(pos, data->screen,
			data->ui.render_switch))
	{
		clear_selected(data);
		mouse_pos[START] = pos;
		mouse_pos[END] = pos;
	}
	else if (action == MRELEASE)
	{
		if ((mouse_pos[START].x != 0) && (mouse_pos[START].y != 0))
			find_selected_objs(mouse_pos, data);
		mouse_pos[START] = vec2i(0, 0);
		mouse_pos[END] = vec2i(0, 0);
	}
}
