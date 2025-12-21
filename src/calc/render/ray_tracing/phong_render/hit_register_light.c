/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_register_light.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 04:16:00 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/17 04:16:00 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "minirt.h"
#include <float.h>

t_object	*hit_light_plane(t_ray *ray, t_scene *scene, float t_min);

t_rgb	hit_register_light(t_ray *ray, t_scene *scene, float light_distance)
{
	t_object	*hit;

	hit = hit_light_plane(ray, scene, light_distance);
	if (hit)
		return (rgb(0, 0, 0));
	hit = hit_aabb_bvh(ray, scene->bvh.aabb_bvh);
	if (hit)
		return (rgb(0, 0, 0));
	return (rgb(1, 1, 1));
}

