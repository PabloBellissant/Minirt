/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ondisplay.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:33:08 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/18 18:42:46 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hbranch	*add_fps(t_data *data, t_hbranch *body);
t_hbranch	*add_render_switch(t_data *data, t_hbranch *body);
t_hbranch	*add_info_display(t_data *data, t_hbranch *body);

int	init_ondisplay(t_data *data, t_hbranch *body)
{
	t_hbranch	*fps;
	t_hbranch	*render_switch;
	t_hbranch	*info_display;

	fps = add_fps(data, body);
	if (!fps)
		return (1);
	render_switch = add_render_switch(data, body);
	if (!render_switch)
		return (1);
	info_display = add_info_display(data, body);
	if (!info_display)
		return (1);
	return (0);
}
