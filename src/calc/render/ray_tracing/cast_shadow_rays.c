/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_shadow_rays.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 06:51:34 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/04 06:51:37 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	cast_shadow_rays(t_hit *hits, t_shadow_ray *shadows, int pixel, t_scene *scene)
{
	t_object	*lights;

	lights = scene->lights.data;
	shadows[pixel].ray.origin = hits[pixel].hit_point;
	shadows[pixel].ray.dir = vec3_sub(lights[0].light.pos, hits[pixel].hit_point);
	shadows[pixel].light_distance = vec3_length(shadows[pixel].ray.dir);
	shadows[pixel].ray.dir = vec3_div_scalar(shadows[pixel].ray.dir, shadows[pixel].light_distance);
	shadows[pixel].light_id = 0;
	shadows[pixel].hit_id = hits[pixel].id;
}

