/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_render_switch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:36:50 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 21:03:29 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline t_hbranch	*add_button_render(t_data *data,
							t_hbranch *render_switch, size_t i)
{
	static const char	*logo_paths[RENDER_MODES] = {WIREFRAME_LOGO_PATH,
		PHONG_LOGO_PATH, PBR_LOGO_PATH, MONTE_CARLO_LOGO_PATH};
	t_hbranch			*button;
	t_hbranch			*logo;

	(void)data;
	button = add_button(render_switch, (t_radius){}, (t_border){.size = 1,
			.color = render_switch->head->style.border, .style = SOLID});
	if (!button)
		return (NULL);
	button->button.action = NULL;
	button->button.arg = NULL;
	button->size = vec2i(35, 35);
	logo = add_image(button, logo_paths[i]);
	logo->anchor = LT;
	logo->x_pos_operation = copy;
	logo->y_pos_operation = copy;
	return (logo);
}

t_hbranch	*add_render_switch(t_data *data, t_hbranch *body)
{
	t_hbranch	*render_switch;
	size_t		i;

	render_switch = add_button_group(body, GROUP_HORZ, GROUP_SWITCH);
	if (!render_switch)
		return (NULL);
	render_switch->anchor = RT;
	render_switch->pos = vec2i(data->screen.x - 15, 15);
	data->ui.render_switch = render_switch;
	data->params.render_mode
		= (int *)&render_switch->button_group.switched_index;
	*(data->params.render_mode) = 0;
	i = 0;
	while (i < RENDER_MODES)
	{
		if (!add_button_render(data, render_switch, i))
			return (NULL);
		i++;
	}
	return (render_switch);
}
