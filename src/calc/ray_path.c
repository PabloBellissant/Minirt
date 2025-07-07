/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:37:35 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/25 17:37:39 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "define.h"
#include "calc.h"
#include "vec3.h"
#include "bvh.h"

t_color	*add_colors(t_color *acc, t_color *newc, float lerp)
{
	acc->r = acc->r + newc->r * lerp;
	acc->g = acc->g + newc->g * lerp;
	acc->b = acc->b + newc->b * lerp;
	return (acc);
}

#define REFLECT 0.2f
#define DIFUSE 0.2f
#define REFLECT_LIMIT 0.00390625f
#include <math.h>

t_color	ray_path(t_ray *restrict ray, t_scene *scene)
{
	t_color		hit_color;
//	t_vec3		random_dir;
	t_ray		current_ray;
	t_color		result_color = (t_color){.rgb = 0};
	int			bounce = 0;
	t_vec3		normal;
	float		temp;
	float		addition;


	current_ray = *ray;
	addition = 1;
	while (bounce < BOUNCE_MAX)
	{
		temp = hit_register(&current_ray, &scene->objects, &hit_color, &normal);
		if (temp == 0)
			return (result_color);
		if (addition < REFLECT_LIMIT)
			return (result_color);
		add_colors(&result_color, &hit_color, (1.0f - REFLECT) * addition);
		// vec3_random(&random_dir);
		// vec3_lerp(&current_ray.dir, &random_dir, 0.01f, &current_ray.dir);
		addition *= REFLECT;
		vec3_dot(&current_ray.dir, &normal, &temp);
		vec3_scale(&normal, 2 * temp);
		vec3_sub(&current_ray.dir, &normal, &current_ray.dir);
		vec3_unit(&current_ray.dir);
		bounce++;
	}
	return (result_color);
}
