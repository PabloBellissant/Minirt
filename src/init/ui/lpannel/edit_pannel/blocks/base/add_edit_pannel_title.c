/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_edit_pannel_title.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 10:55:47 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 19:44:03 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hbranch	*add_edit_pannel_title(t_hbranch *obj_edit, int *y_size,
				char *title)
{
	t_hbranch	*textbox;

	textbox = add_textbox(obj_edit,
			(t_text)
		{
			.font_size = 4,
			.fg = (t_rgba_int){.rgba = WHITE},
		},
			CENTER_ALIGN,
			NO_WRAPPING);
	ft_strlcpy(textbox->textbox.content, title, MAX_CHARS);
	textbox->textbox.vert_align = MIDDLE_ALIGN;
	textbox->anchor = LT;
	textbox->size = vec2i(obj_edit->size.x, BLOCK_HEIGHT * 2);
	textbox->pos = vec2i_zero();
	textbox->pos.y += *y_size;
	*y_size += textbox->size.y;
	return (textbox);
}
