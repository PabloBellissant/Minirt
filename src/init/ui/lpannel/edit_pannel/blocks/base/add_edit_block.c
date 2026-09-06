/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_edit_block.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:48:24 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 11:29:17 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hbranch	*add_edit_block(t_hbranch *edit_zone, int *y_size)
{
	t_hbranch	*form_block;

	form_block = add_box(edit_zone, (t_radius){0}, (t_border){0});
	form_block->size = vec2i(edit_zone->size.x - BLOCK_PADDING * 2, *y_size);
	*y_size += BLOCK_PADDING;
	form_block->pos = vec2i(BLOCK_PADDING, *y_size);
	form_block->anchor = LT;
	precompute_geometry(form_block, 0, edit_zone->childs->num_elements);
	return (form_block);
}
