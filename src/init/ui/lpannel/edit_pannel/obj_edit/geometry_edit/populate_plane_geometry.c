/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_plane_geometry.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 21:19:39 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 21:19:47 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	populate_plane_geometry(t_data *data, t_hbranch *obj_edit, int *y_size,
		t_plane *plane)
{
	t_block_util	bl;

	bl = (t_block_util){.data = data, .comp = obj_edit,
		.y_size = y_size, .name = "Rotation", .v_ptr = &plane->normal};
	if (add_vec3_edit(bl) != 0)
		return (1);
	*y_size += INBLOCK_PADDING;
	return (0);
}
