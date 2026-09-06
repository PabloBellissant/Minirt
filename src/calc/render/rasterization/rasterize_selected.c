/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize_selected.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 07:23:38 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/12 08:02:12 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	rasterize_selected(t_img_data *img, t_vector objects, t_camera *cam)
{
	size_t		i;
	t_object	**obj;

	obj = objects.data;
	i = 0;
	while (i < objects.num_elements)
	{
		if (i == 0)
			rasterize_outline_object(img, obj[i], cam, drgb_int(FSELECT_COLOR));
		else
			rasterize_outline_object(img, obj[i], cam, drgb_int(SELECT_COLOR));
		++i;
	}
}
