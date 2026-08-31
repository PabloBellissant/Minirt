/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_render_edit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 08:49:47 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 20:27:23 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	populate_cam_params(t_data *data, t_hbranch *render_edit, int *y_size);
int	populate_export_buttons(t_data *data, t_hbranch *render_edit, int *y_size);

t_hbranch	*populate_render_edit(t_data *data, t_hbranch *render_edit,
				int *y_size)
{
	t_hbranch	*textbox;

	textbox = add_edit_pannel_title(render_edit, y_size, "Render");
	if (!textbox)
		return (NULL);
	if (populate_cam_params(data, render_edit, y_size) != 0)
		return (NULL);
	if (populate_export_buttons(data, render_edit, y_size) != 0)
		return (NULL);
	return (textbox);
}
