/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   hit_register.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: pabellis <pabellis@student.forty2.fr>	  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/08/08 02:48:48 by pabellis		  #+#	#+#			 */
/*   Updated: 2025/08/19 23:37:29 by pabellis		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include <float.h>

#include "vectors.h"
#include "calc.h"

#define OFFSET 0.001f

void	hit_register_obj(t_ray *restrict ray, t_object *restrict objects)
{
	t_vec3	hit_point;
	t_vec3	axis;
	t_vec3	to_hit;

	hit_point = vec3_scale(ray->dir, objects->t);
	hit_point = vec3_add(ray->pos, hit_point);
	if (objects->type == SPHERE)
	{
		ray->hit_normal = vec3_sub(hit_point, objects->sphere.pos);
		ray->hit_normal = unsafe_vec3_normalize(ray->hit_normal);
		ray->hit_rgb = objects->sphere.rgb;
	}
	else if (objects->type == PLANE)
	{
		ray->hit_normal = objects->plane.normal;
		ray->hit_rgb = objects->plane.rgb;
	}
	else if (objects->type == CYLINDER)
	{
		axis = objects->cylinder.rot;
		to_hit = vec3_sub(hit_point, objects->cylinder.pos);
		axis = vec3_scale(axis, vec3_dot(to_hit, axis));
		axis = vec3_add(objects->cylinder.pos, axis);
		ray->hit_normal = vec3_sub(hit_point, axis);
		ray->hit_normal = unsafe_vec3_normalize(ray->hit_normal);
		ray->hit_rgb = objects->cylinder.rgb;
	}
	ray->pos = hit_point;
}

t_object	*hit_sphere_bvh(t_ray *ray, t_sphere_bvh *bvh);

float	hit_register(t_ray *ray, t_scene *scene, t_object **hit_object)
{
	t_object	*bvh_ret;

	if (scene->bvh.bvh_mode == 0)
		bvh_ret = hit_sphere_bvh(ray, scene->bvh.sphere_bvh);
	else if (scene->bvh.bvh_mode == 1)
		bvh_ret = hit_aabb_bvh(ray, scene->bvh.aabb_bvh);
	else
		bvh_ret = hit_aabb_bvh(ray, scene->bvh.aabb_bvh); // will be obb.
	if (bvh_ret)
		(*hit_object) = hit_reg_plane(ray, scene, bvh_ret->t);
	else
		(*hit_object) = hit_reg_plane(ray, scene, FLT_MAX);
	if (bvh_ret != NULL)
	{
		if (!(*hit_object) || bvh_ret->t < (*hit_object)->t)
			(*hit_object) = bvh_ret;
	}
	else if (!(*hit_object) || (*hit_object)->t == FLT_MAX)
		return (0);
	hit_register_obj(ray, (*hit_object));
	return ((*hit_object)->t);
}
