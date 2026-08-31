/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ks_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:13:11 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 20:36:15 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	**`Ks` (Specular Color)** - **0.0 to 1.0** per RGB channel
	- RGB values between 0.0 and 1.0
*/
int	add_ks_edit(t_data *data, t_hbranch *obj_edit, int *y_size, t_mat *mat)
{
	t_block_util	bl;

	bl = (t_block_util){.data = data, .comp = obj_edit, .y_size = y_size,
		.rgb_ptr = &mat->ks, .name = "Specular"};
	return (add_color_edit(bl));
}
