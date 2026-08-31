/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_lpannel_switch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:58:21 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 14:18:50 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define OBJ_EDIT_NAME		"Object Edit"
#define RENDER_EDIT_NAME	"Render Options"
#define LPANNEL_MODES		2

static inline t_hbranch	*add_text_lpannel_switch(t_data *data,
							t_hbranch *button, size_t i)
{
	static const char	*text_names[LPANNEL_MODES] = {OBJ_EDIT_NAME,
		RENDER_EDIT_NAME};
	t_hbranch			*text;

	(void)data;
	text = add_textbox(button,
			(t_text)
		{
			.font_size = 3,
			.fg = (t_rgba_int){.rgba = WHITE},
		},
			CENTER_ALIGN,
			NO_WRAPPING);
	if (!text)
		return (NULL);
	ft_strlcpy(text->textbox.content, text_names[i],
		ft_strlen(text_names[i]) + 1);
	text->textbox.vert_align = MIDDLE_ALIGN;
	text->anchor = LT;
	text->x_pos_operation = copy;
	text->y_pos_operation = copy;
	text->x_size_operation = copy;
	text->y_size_operation = copy;
	return (text);
}

static inline t_hbranch	*add_button_edit(t_data *data,
							t_hbranch *lpannel_switch, size_t i)
{
	t_hbranch	*button;

	(void)data;
	button = add_button(lpannel_switch, (t_radius){}, (t_border){.size = 1,
			.color = lpannel_switch->head->style.border, .style = SOLID});
	if (!button)
		return (NULL);
	button->button.action2
		= (t_action2 *)rebuild_inner_edit;
	button->button.args2[0] = data;
	button->button.args2[1] = data->ui.edit_pannel;
	button->size = vec2i((float)(lpannel_switch->size.x) / (float)LPANNEL_MODES,
			lpannel_switch->size.y);
	return (add_text_lpannel_switch(data, button, i));
}

t_hbranch	*add_lpannel_switch(t_data *data, t_hbranch *lpannel)
{
	t_hbranch	*lpannel_switch;
	size_t		i;

	(void)data;
	lpannel_switch = add_button_group(lpannel, GROUP_HORZ, GROUP_SWITCH);
	lpannel_switch->anchor = RT;
	lpannel_switch->pos = vec2i(lpannel->pos.x - 4,
			lpannel->pos.y + 2 + data->ui.scene_height);
	lpannel_switch->size = vec2i(lpannel->size.x,
			data->ui.lpannel_switch_height);
	lpannel_switch->size = vec2i_sub_scalar(lpannel_switch->size, 6);
	data->ui.lpannel_switch = lpannel_switch;
	data->ui.edit_mode
		= (int *)&lpannel_switch->button_group.switched_index;
	*(data->ui.edit_mode) = 0;
	i = 0;
	while (i < LPANNEL_MODES)
	{
		if (!add_button_edit(data, lpannel_switch, i))
			return (NULL);
		i++;
	}
	return (lpannel_switch);
}
