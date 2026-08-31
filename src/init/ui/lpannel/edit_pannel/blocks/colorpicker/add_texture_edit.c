/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_texture_edit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:47:37 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 20:12:05 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	add_texture_edit(t_block_util bl)
{
	t_hbranch		*form_block;
	t_hbranch		*title;
	t_hbranch		*color;
	t_block_util	bl2;

	form_block = add_edit_block(bl.comp, bl.y_size);
	if (!form_block)
		return (1);
	bl2 = (t_block_util){.comp = form_block,
		.y_size = bl.y_size, .name = bl.name};
	title = add_block_title(bl2);
	if (!title)
		return (1);
	color = add_colorpicker(form_block, rgb_itof(rgb_int(bl.tex_ptr->pixels[0],
					bl.tex_ptr->pixels[1], bl.tex_ptr->pixels[2])));
	if (!color)
		return (1);
	color->anchor = RT;
	color->pos = vec2i(form_block->pos.x + form_block->size.x, *bl.y_size);
	color->colorpicker.action2 = (t_action2 *)apply_to_tex_col;
	color->colorpicker.args2[0] = bl.tex_ptr->pixels;
	color->colorpicker.args2[1] = bl.data;
	*bl.y_size += color->form.box.size.y;
	form_block->size.y = *bl.y_size - form_block->size.y;
	return (0);
}
