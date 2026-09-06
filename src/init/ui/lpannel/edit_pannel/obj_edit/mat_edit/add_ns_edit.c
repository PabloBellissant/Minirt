/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ns_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:17:09 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 20:37:12 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	**`Ns` (Shininess/Specular Exponent)** - **0 to 1000**
	- 0 = very rough/dull surface
	- 1000 = mirror-like polish
*/
int	add_ns_edit(t_data *data, t_hbranch *obj_edit, int *y_size, t_mat *mat)
{
	t_block_util	bl;

	bl = (t_block_util){.data = data, .comp = obj_edit, .y_size = y_size,
		.clf_ptr = &mat->ns, .name = "Shininess"};
	return (add_slider_edit(bl, 0.f, 1000.f, false));
}
