/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_info_display_selected.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:47:41 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 19:19:10 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define INFO_STR_SELECT "Objects     %d/%d\n\
Vertices    %d/%d\n\
Edges       %d/%d\n\
Triangles   %d/%d"

static inline int	get_scene_info_selected(t_vector v)
{
	size_t		i;
	t_object	**obj;
	int			tri_num;

	tri_num = 0;
	i = 0;
	obj = v.data;
	while (i < v.num_elements)
	{
		if (obj[i]->type == TRIANGLE)
			tri_num++;
		i++;
	}
	return (tri_num);
}

void	update_info_display_selected(t_data *data, int tri_num)
{
	int	select_tri_num;

	select_tri_num = get_scene_info_selected(data->ui.selection.selected);
	strf(data->ui.info_buffer, MAX_CHARS, INFO_STR_SELECT,
		(int)data->ui.selection.selected.num_elements - select_tri_num,
		(int)data->scene.objects.num_elements - tri_num,
		(int)((float)select_tri_num * 0.5f) + ((bool)(select_tri_num) * 2),
		(int)((float)tri_num * 0.5f) + ((bool)(tri_num) * 2),
		(int)((float)select_tri_num * 3.f / 2.f),
		(int)((float)tri_num * 3.f / 2.f),
		select_tri_num, tri_num);
}
