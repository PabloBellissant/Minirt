/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cam_entry.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:13:14 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 19:23:06 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define CAMERA_LABEL "Camera"

t_hbranch	*add_cam_entry(t_hbranch *scene_list, size_t *num_entries,
				t_data *data)
{
	t_hbranch	*entry;
	t_camera	camera;

	camera = data->scene.camera;
	(void)camera;
	entry = add_scene_entry(scene_list, CAMERA_LABEL, NULL, data);
	entry->pos.y += *num_entries * ENTRY_HEIGHT;
	if (*num_entries % 2)
		entry->box.color.a = 120;
	else
		entry->box.color.a = 180;
	(*num_entries)++;
	return (entry);
}
