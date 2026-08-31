/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_form_block.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:53:09 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 19:43:43 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline t_hbranch	*add_form_block_label(t_block_util bl, t_hbranch *form)
{
	t_hbranch	*block_label;

	block_label = add_textbox(bl.comp,
			(t_text)
		{
			.font_size = 3,
			.fg = (t_rgba_int){.rgba = WHITE},
		},
			CENTER_ALIGN,
			NO_WRAPPING);
	if (!block_label)
		return (NULL);
	ft_strlcpy(block_label->textbox.content, bl.name, ft_strlen(bl.name) + 1);
	block_label->textbox.vert_align = MIDDLE_ALIGN;
	block_label->size.y = form->size.y;
	block_label->size = vec2i(BLOCK_HEIGHT, form->size.y);
	block_label->anchor = RT;
	block_label->pos = form->_lt;
	return (block_label);
}

/*
	Will add a form and an inlined label if specified
*/
t_hbranch	*add_form_block(t_block_util bl)
{
	t_hbranch	*form;
	t_hbranch	*label;

	form = add_form(bl.comp, bl.f_ptr, FORM_FLOAT, "u");
	form->anchor = RT;
	form->pos = vec2i(bl.comp->pos.x + bl.comp->size.x, *bl.y_size);
	form->form.action = (t_action *)reload_gpu;
	form->form.arg = bl.data;
	precompute_geometry(form, 0, bl.comp->childs->num_elements);
	if (bl.name)
	{
		label = add_form_block_label(bl, form);
		if (!label)
			return (NULL);
	}
	*bl.y_size += BLOCK_HEIGHT + BLOCK_PADDING;
	return (form);
}
