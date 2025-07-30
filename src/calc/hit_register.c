/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   hit_register.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/05/25 17:42:26 by pabellis		  #+#	#+#			 */
/*   Updated: 2025/07/30 07:57:24 by jaubry--		 ###   ########lyon.fr   */
/*																			*/
/* ************************************************************************** */

#include <float.h>
#include "struct.h"
#include "vec3.h"
#include "calc.h"

#define OFFSET 0.001f

float hit_register(t_ray *restrict ray, t_vector *restrict obj_vec, t_color *restrict color, t_vec3 *restrict normal)
{
	t_vec3		hit_point;
	t_object	*objects;
	float		t_min;
	int			i_min;
	float		t;
	int			i;

	objects = obj_vec->data;
	i_min = 0;
	i = 0;
	t_min = FLT_MAX;
	while (i < (int)obj_vec->num_elements)
	{
		if (objects[i].f(ray, &objects[i], &t))
		{
			if (t < t_min)
			{
				i_min = i;
				t_min = t;
			}
		}
		++i;
	}
	if (t_min == FLT_MAX)
		return (0);
	objects = &objects[i_min];
	t_vec3 hit_dir;
	hit_dir = ray->dir;
	vec3_scale(&hit_dir, t_min);
	vec3_add(&ray->pos, &hit_dir, &hit_point);
	if (objects->type == SPHERE)
	{
		vec3_sub(&hit_point, &objects->sphere.pos, normal);
		vec3_normalize(normal);  // Proper normalization
		*color = objects->sphere.color;
	}
	else if ((objects->type == PLANE) || (objects->type == TRIANGLE))
	{
		*normal = objects->plane.normal;
		vec3_normalize(normal);  // Ensure plane normals are normalized too
		*color = objects->plane.color;
	}
	else  // cylinder
	{
		vec3_sub(&hit_point, &objects->cylinder.pos, normal);
		vec3_normalize(normal);  // This is still incomplete for cylinders
		*color = objects->cylinder.color;
	}
	ray->pos = hit_point;
	return (t_min);
}
