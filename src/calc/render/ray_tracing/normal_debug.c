/* **********************l*************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:55:34 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/16 01:44:23 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors_types.h"
#include "minirt.h"
#include "calc.h"
#include "mlx_draw.h"
#include "rgb_operations.h"
#include "rgb_scalar.h"
#include "vec3_operations.h"
#include "vec3_special1.h"

void	normal_debug(t_buffers *buffers, int pixel)
{
	buffers->rays[buffers->hits[pixel].id].accumulated_color = rgb_add_scalar(rgb_scale(buffers->hits[pixel].normal, 0.5f), 0.5f);
	buffers->rays[buffers->hits[pixel].id].through_power = rgb(0, 0, 0);
}

void	normal_debug_loop(t_buffers *buffers, int count)
{
	int			pixel;

	pixel = 0;
	while (pixel < count)
	{
		normal_debug(buffers, pixel);
		++pixel;
	}
}


