/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reload_scene_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 19:14:18 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 19:14:36 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		free_before_refill(t_scene *scene);

void	reload_gpu(t_hbranch *hbranch, t_data *data)
{
	(void)hbranch;
	free_before_refill(&data->scene);
	fill_gpu_data(&data->cl, &data->scene);
}
