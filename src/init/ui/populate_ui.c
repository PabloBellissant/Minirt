/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_ui.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:37:56 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/18 19:46:17 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_ondisplay(t_data *data, t_hbranch *body);
int	init_lpannel(t_data *data, t_hbranch *body);

int	populate_ui(t_data *data, t_hbranch *body)
{
	if (init_ondisplay(data, body) != 0)
		return (1);
	if (init_lpannel(data, body) != 0)
		return (1);
	return (0);
}
