/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_fps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:32:41 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 19:20:13 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hbranch	*add_fps(t_data *data, t_hbranch *body)
{
	t_hbranch	*fps;

	fps = add_textbox(body,
			(t_text)
		{
			.font_size = 4,
			.fg = (t_rgba_int){.rgba = YELLOW},
		},
			LEFT_ALIGN,
			NO_WRAPPING);
	fps->textbox.vert_align = BASELINE_ALIGN;
	fps->anchor = LT;
	data->ui.fps_buffer = fps->textbox.content;
	return (fps);
}
