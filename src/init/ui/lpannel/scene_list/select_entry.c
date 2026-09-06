/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_entry.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 14:33:20 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/18 14:33:32 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	select_entry(t_hbranch *hbranch, void *arg1, void *arg2)
{
	t_data		*data;
	t_object	*obj;

	(void)hbranch;
	if (!arg1 || !arg2)
		return ;
	obj = (t_object *)arg1;
	data = (t_data *)arg2;
	clear_selected(data);
	select_obj(data, obj);
}
