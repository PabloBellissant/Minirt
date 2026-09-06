/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_float_edit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:36:13 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 19:54:10 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	add_float_edit(t_block_util bl)
{
	t_hbranch		*form_block;
	t_hbranch		*title;
	t_hbranch		*form;
	t_block_util	bl2;
	t_block_util	bl3;

	form_block = add_edit_block(bl.comp, bl.y_size);
	if (!form_block)
		return (1);
	bl2 = (t_block_util){.comp = form_block,
		.y_size = bl.y_size, .name = bl.name};
	title = add_block_title(bl2);
	if (!title)
		return (1);
	bl3 = (t_block_util){.data = bl.data, .comp = form_block,
		.y_size = bl.y_size, .f_ptr = bl.f_ptr, .name = NULL};
	form = add_form_block(bl3);
	if (!form)
		return (1);
	form_block->size.y = *bl.y_size - form_block->size.y;
	return (0);
}
