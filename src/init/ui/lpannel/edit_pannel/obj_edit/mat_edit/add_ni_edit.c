/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ni_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:14:23 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 20:36:44 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	**`Ni` (Index of Refraction)** - **0.001 to 10** (typical: 1.0 to 3.0)
	- 1.0 = air/vacuum
	- 1.33 = water
	- 1.5-1.9 = glass
	- 2.4 = diamond
*/
int	add_ni_edit(t_data *data, t_hbranch *obj_edit, int *y_size, t_mat *mat)
{
	t_block_util	bl;

	bl = (t_block_util){.data = data, .comp = obj_edit, .y_size = y_size,
		.clf_ptr = &mat->ni, .name = "Index of reflection"};
	return (add_slider_edit(bl, 0.001, 10, false));
}
