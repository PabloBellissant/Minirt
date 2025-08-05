/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   hit_register.c                                     :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/05/25 17:42:26 by pabellis		  #+#	#+#			 */
/*   Updated: 2025/08/05 04:19:30 by jaubry--         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <float.h>

#include "vec3.h"
#include "calc.h"

#define OFFSET 0.001f

static void	hit_register_obj(t_ray *restrict ray,
	t_object *restrict objects, float t_min)
{
	t_vec3	hit_dir;
	t_vec3	hit_point;

	hit_dir = ray->dir;
	vec3_scale(&hit_dir, t_min);
	vec3_add(&ray->pos, &hit_dir, &hit_point);
	if (objects->type == SPHERE)
	{
		vec3_sub(&hit_point, &objects->sphere.pos, &ray->hit_normal);
		ray->hit_rgb = objects->sphere.rgb;
	}
	else if (objects->type == PLANE)
	{
		ray->hit_normal = objects->plane.normal;
		ray->hit_rgb = objects->plane.rgb;
	}
	else
	{
		vec3_sub(&hit_point, &objects->cylinder.pos, &ray->hit_normal);
		ray->hit_rgb = objects->cylinder.rgb;
	}
	vec3_normalize(&ray->hit_normal);
	ray->pos = hit_point;
}

float	hit_register(t_ray *restrict ray, t_vector *restrict obj_vec)
{
	t_object	*objects;
	float		t_n_min[2];
	int			i_n_min[2];

	objects = obj_vec->data;
	i_n_min[0] = 0;
	i_n_min[1] = 0;
	t_n_min[1] = FLT_MAX;
	while (i_n_min[0] < (int)obj_vec->num_elements)
	{
		if (objects[i_n_min[0]].f(ray, &objects[i_n_min[0]], &t_n_min[0]))
		{
			if (t_n_min[0] < t_n_min[1])
			{
				i_n_min[1] = i_n_min[0];
				t_n_min[1] = t_n_min[0];
			}
		}
		++i_n_min[0];
	}
	if (t_n_min[1] == FLT_MAX)
		return (0);
	objects = &objects[i_n_min[1]];
	hit_register_obj(ray, objects, t_n_min[1]);
	return (t_n_min[1]);
}
