/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_obj_geometry.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 15:44:46 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 11:26:29 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	populate_sphere_geometry(t_data *data, t_hbranch *obj_edit, int *y_size,
		t_sphere *sphere);
int	populate_plane_geometry(t_data *data, t_hbranch *obj_edit, int *y_size,
		t_plane *plane);

/*
	Object always have the same 3 fields for position
	But they can have no rotation (SPHERE)
	And can have different scaling (XYZ scaling / Radius / No scaling)
*/
int	populate_obj_geometry(t_data *data, t_hbranch *obj_edit, int *y_size,
		t_object *obj)
{
	int				ret;
	t_block_util	bl;

	ret = 0;
	bl = (t_block_util){.data = data, .comp = obj_edit, .y_size = y_size,
		.name = "Location", .v_ptr = &obj->pos};
	if (add_vec3_edit(bl) != 0)
		return (1);
	*y_size += INBLOCK_PADDING;
	if (obj->type == SPHERE)
		ret = populate_sphere_geometry(data, obj_edit, y_size, &obj->sphere);
	else if (obj->type == PLANE)
		ret = populate_plane_geometry(data, obj_edit, y_size, &obj->plane);
	return (ret);
}
