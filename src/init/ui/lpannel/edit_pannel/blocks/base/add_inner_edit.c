/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_inner_edit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 08:54:58 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 11:31:15 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hbranch	*add_inner_edit(t_hbranch *edit_pannel)
{
	const int	radius_offset = edit_pannel->box.radius.full / 2;
	t_hbranch	*inner_edit;

	inner_edit = add_scrollbox(edit_pannel);
	if (!inner_edit)
		return (NULL);
	inner_edit->pos = vec2i(edit_pannel->pos.x - radius_offset,
			edit_pannel->pos.y + radius_offset);
	inner_edit->anchor = RT;
	inner_edit->size = vec2i_sub_scalar(edit_pannel->size,
			edit_pannel->box.radius.full);
	inner_edit->scrollbox.inside->size = inner_edit->size;
	return (inner_edit);
}
