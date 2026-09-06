/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_info_display_global.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:47:05 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 19:18:58 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define INFO_STR "Objects     %d\n\
Vertices    %d\n\
Edges       %d\n\
Triangles   %d"

int	get_scene_info(t_vector v)
{
	size_t		i;
	t_object	*obj;
	int			tri_num;

	tri_num = 0;
	i = 0;
	obj = v.data;
	while (i < v.num_elements)
	{
		if (obj[i].type == TRIANGLE)
			tri_num++;
		i++;
	}
	return (tri_num);
}

void	update_info_display_global(t_data *data, int tri_num)
{
	strf(data->ui.info_buffer, MAX_CHARS, INFO_STR,
		(int)data->scene.objects.num_elements - tri_num,
		(int)((float)tri_num * 0.5f) + ((bool)(tri_num) * 2),
		(int)((float)tri_num * 3.f / 2.f),
		tri_num);
}
