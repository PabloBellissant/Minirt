/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_grayscale_edit.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:46:32 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 20:11:35 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	add_grayscale_edit(t_block_util bl)
{
	t_hbranch		*title;
	t_hbranch		*slider;
	t_block_util	bl2;

	bl2 = (t_block_util){.comp = add_edit_block(bl.comp, bl.y_size),
		.y_size = bl.y_size, .name = bl.name};
	if (!bl2.comp)
		return (1);
	title = add_block_title(bl2);
	if (!title)
		return (1);
	slider = add_slider(bl2.comp, NULL, 0, 255);
	if (!slider)
		return (1);
	slider->anchor = RT;
	slider->pos = vec2i(bl2.comp->pos.x + bl2.comp->size.x, *bl.y_size);
	slider->size = vec2i(bl2.comp->size.x, 36);
	slider->slider.action2 = (t_action2 *)apply_to_grayscale;
	slider->slider.args2[0] = bl.tex_ptr->pixels;
	slider->slider.args2[1] = bl.data;
	slider->slider.value = (float)clamp_float_to_byte(bl.tex_ptr->pixels[0]);
	*bl.y_size += slider->size.y;
	bl2.comp->size.y = *bl.y_size - bl2.comp->size.y;
	return (0);
}
