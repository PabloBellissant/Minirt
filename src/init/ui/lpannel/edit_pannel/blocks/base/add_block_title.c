/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_block_title.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:38:51 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 19:43:22 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hbranch	*add_block_title(t_block_util bl)
{
	t_hbranch	*block_title;

	block_title = add_textbox(bl.comp,
			(t_text)
		{
			.font_size = 3,
			.fg = (t_rgba_int){.rgba = WHITE},
		},
			LEFT_ALIGN,
			NO_WRAPPING);
	if (!block_title)
		return (NULL);
	ft_strlcpy(block_title->textbox.content, bl.name, ft_strlen(bl.name) + 1);
	block_title->textbox.vert_align = MIDDLE_ALIGN;
	block_title->anchor = LT;
	block_title->size = vec2i(bl.comp->size.x, BLOCK_HEIGHT);
	block_title->pos = bl.comp->pos;
	*bl.y_size += block_title->size.y;
	return (block_title);
}
