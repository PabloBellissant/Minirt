/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_sphere_geometry.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:45:13 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 20:46:45 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	populate_sphere_geometry(t_data *data, t_hbranch *obj_edit, int *y_size,
		t_sphere *sphere)
{
	t_block_util	bl;

	bl = (t_block_util){.data = data, .comp = obj_edit,
		.y_size = y_size, .name = "Radius", .f_ptr = &sphere->radius};
	if (add_float_edit(bl) != 0)
		return (1);
	*y_size += INBLOCK_PADDING;
	return (0);
}
