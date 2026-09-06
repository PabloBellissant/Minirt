/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_edit_pannel.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:52:48 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 10:39:41 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_edit_pannel(t_data *data)
{
	if (data->ui.inner_edit)
	{
		delete_node_childs(data->ui.edit_pannel);
		data->ui.inner_edit = NULL;
	}
}
