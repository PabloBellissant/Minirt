/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_skybox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 12:42:19 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/14 02:25:09 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rgb_operations.h"
#include "rgb_scalar.h"
#include "vec3_operations.h"
#include "vec3_scalar.h"

t_vec3	vec3_inv(t_vec3 vec);

void	draw_skybox(int pixel, t_buffers bu, int texture_id, t_texture *texture)
{
	t_rgb	color;

	if (bu.rays[bu.hits[pixel].id].active == false)
		return ;
	color = sample_texture(texture, texture_id, bu.hits[pixel].uv);
	bu.rays[bu.hits[pixel].id].accumulated_color = rgb_add(bu.rays[bu.hits[pixel].id].accumulated_color, rgb_mult(color, bu.rays[bu.hits[pixel].id].through_power));
	if (bu.rays[bu.hits[pixel].id].refract.count == 0)
	{
		bu.rays[bu.hits[pixel].id].active = false;
		return ;
	}
	--bu.rays[bu.hits[pixel].id].refract.count;
	bu.rays[bu.hits[pixel].id].dir = bu.rays[bu.hits[pixel].id].refract.dir[bu.rays[bu.hits[pixel].id].refract.count];
	bu.rays[bu.hits[pixel].id].inv_dir = vec3_inv(bu.rays[bu.hits[pixel].id].dir);
	bu.rays[bu.hits[pixel].id].origin = bu.rays[bu.hits[pixel].id].refract.origin[bu.rays[bu.hits[pixel].id].refract.count];
	bu.rays[bu.hits[pixel].id].through_power = bu.rays[bu.hits[pixel].id].refract.through_power[bu.rays[bu.hits[pixel].id].refract.count];
	bu.hits[pixel].hit = true;
}

void	draw_skybox_loop(t_buffers bu, int texture_id, t_texture *texture, int size)
{
	int	i;

	i = size;
	while (i < (WIDTH * HEIGHT))
	{
		draw_skybox(i, bu, texture_id, texture);
		++i;
	}
}

