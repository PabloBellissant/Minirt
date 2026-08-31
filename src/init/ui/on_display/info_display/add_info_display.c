/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_info_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:39:16 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 19:19:52 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define INFO_DISPLAY_X 50
#define INFO_DISPLAY_Y 240
#define INFO_DISPLAY_OPACITY 15

t_hbranch	*add_info_display(t_data *data, t_hbranch *body)
{
	t_hbranch	*info;

	info = add_textbox(body,
			(t_text)
		{
			.font_size = 2,
			.fg = data->ui.htree.style.highlight,
		},
			LEFT_ALIGN,
			NO_WRAPPING);
	if (!info)
		return (NULL);
	data->ui.info_buffer = info->textbox.content;
	info->textbox.fg.a = INFO_DISPLAY_OPACITY;
	info->textbox.vert_align = BASELINE_ALIGN;
	info->anchor = LT;
	info->pos = vec2i(INFO_DISPLAY_X, INFO_DISPLAY_Y);
	update_info_display(data);
	return (info);
}
