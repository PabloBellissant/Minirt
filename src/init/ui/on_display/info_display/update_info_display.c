/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_info_display.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:45:13 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/18 18:45:27 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		get_scene_info(t_vector v);
void	update_info_display_global(t_data *data, int tri_num);
void	update_info_display_selected(t_data *data, int tri_num);

void	update_info_display(t_data *data)
{
	int	tri_num;

	tri_num = get_scene_info(data->scene.objects);
	ft_bzero(data->ui.info_buffer, sizeof(data->ui.info_buffer));
	if (data->ui.selection.selected.num_elements)
		update_info_display_selected(data, tri_num);
	else
		update_info_display_global(data, tri_num);
}
