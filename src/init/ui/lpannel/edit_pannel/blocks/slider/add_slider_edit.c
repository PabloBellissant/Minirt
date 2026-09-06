/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_slider_edit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:48:05 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 20:15:40 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	add_slider_edit(t_block_util bl, float start, float stop, bool linear)
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
	slider = add_slider(bl2.comp, bl.clf_ptr, start, stop);
	if (!slider)
		return (1);
	slider->anchor = RT;
	slider->pos = vec2i(bl2.comp->pos.x + bl2.comp->size.x, *bl.y_size);
	slider->size = vec2i(bl2.comp->size.x, 36);
	slider->slider.action = (t_action *)apply_mat_changes;
	slider->slider.arg = bl.data;
	slider->slider.linear_step = linear;
	*bl.y_size += slider->size.y;
	bl2.comp->size.y = *bl.y_size - bl2.comp->size.y;
	return (0);
}
