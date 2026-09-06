/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_vec3_edit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 16:11:26 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 20:06:30 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	Vec3 pack 
	Has a title
	and has 3 forms with label associated
	- can only represent X Y Z (scaling, position, rotation)
*/
int	add_vec3_edit(t_block_util bl)
{
	const char		*names[3] = {"X", "Y", "Z"};
	t_hbranch		*form[3];
	size_t			i;
	t_block_util	bl2;
	t_block_util	bl3;

	bl2 = (t_block_util){.comp = add_edit_block(bl.comp, bl.y_size),
		.y_size = bl.y_size, .name = bl.name};
	if (!bl2.comp)
		return (1);
	if (!add_block_title(bl2))
		return (1);
	i = 0;
	while (i < 3)
	{
		bl3 = (t_block_util){.data = bl.data, .comp = bl2.comp, .y_size
			= bl.y_size, .f_ptr = &(bl.v_ptr)->s[i], .name = (char *)names[i]};
		form[i] = add_form_block(bl3);
		if (!form[i])
			return (1);
		i++;
	}
	bl2.comp->size.y = *bl.y_size - bl2.comp->size.y;
	return (0);
}
