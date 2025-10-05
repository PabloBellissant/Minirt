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

unsigned int sample_texture(t_scene *scene, float u, float v)
{
	int x = (int)(u * (scene->tex_width - 1));
	int y = (int)(v * (scene->tex_height - 1));

	int offset = y * scene->tex_size_line + x * (scene->tex_bpp / 8);

	return *(unsigned int *)(scene->pixels + offset);
}

t_vec3 texture_to_vec3(unsigned int color)
{
	t_vec3 result;

	result.x = ((color >> 16) & 0xFF) / 255.0f;
	result.y = ((color >> 8) & 0xFF) / 255.0f;
	result.z = (color & 0xFF) / 255.0f;

	return result;
}
# define NORMAL_DEBUG 0
void    hit_register_obj(t_ray *restrict ray, t_object *restrict o, t_scene *scene)
{
    t_vec3 hit_point;
    t_vec3 axis;
    t_vec3 to_hit;

    hit_point = vec3_scale(ray->dir, o->t);
    hit_point = vec3_add(ray->pos, hit_point);
    if (o->type == SPHERE)
    {
       ray->hit_normal = vec3_sub(hit_point, o->sphere.pos);
       ray->hit_normal = unsafe_vec3_normalize(ray->hit_normal);

       float u = 0.5f + atan2f(ray->hit_normal.z, ray->hit_normal.x) / (2.0f * M_PI);
       float v = 0.5f - asinf(ray->hit_normal.y) / M_PI;

       ray->hit_rgb = texture_to_vec3(sample_texture(scene, u, v));
    }
    else if (o->type == PLANE)
    {
       ray->hit_normal = o->plane.normal;

       // ✅ Calcul des UV pour le plan
       // Crée deux vecteurs perpendiculaires au plan pour former une base 2D
       t_vec3 tangent, bitangent;

       // Trouve un vecteur perpendiculaire à la normale
       if (fabsf(o->plane.normal.y) > 0.9f)
          tangent = vec3_cross(o->plane.normal, vec3(1, 0, 0));
       else
          tangent = vec3_cross(o->plane.normal, vec3(0, 1, 0));
       tangent = unsafe_vec3_normalize(tangent);

       bitangent = vec3_cross(o->plane.normal, tangent);
       bitangent = unsafe_vec3_normalize(bitangent);

       // Point relatif à la position du plan
       t_vec3 local_point = vec3_sub(hit_point, o->plane.pos);

       // Projette sur les axes tangent/bitangent et wrap pour répéter la texture
       float u = vec3_dot(local_point, tangent) * 0.1f;  // 0.1 = scale de répétition
       float v = vec3_dot(local_point, bitangent) * 0.1f;

       // Wrap (modulo pour répéter la texture)
       u = u - floorf(u);
       v = v - floorf(v);

       // Sample la texture
       unsigned int tex_color = sample_texture(scene, u, v);
       ray->hit_rgb = texture_to_vec3(tex_color);
    }
    else if (o->type == TRIANGLE)
    {
       t_vec3 v0v1 = vec3_sub(o->triangle.p1.pos, o->triangle.p0.pos);
       t_vec3 v0v2 = vec3_sub(o->triangle.p2.pos, o->triangle.p0.pos);
       t_vec3 v0p = vec3_sub(hit_point, o->triangle.p0.pos);

       float d00 = vec3_dot(v0v1, v0v1);
       float d01 = vec3_dot(v0v1, v0v2);
       float d11 = vec3_dot(v0v2, v0v2);
       float d20 = vec3_dot(v0p, v0v1);
       float d21 = vec3_dot(v0p, v0v2);

       float denom = d00 * d11 - d01 * d01;
    	// Calcul des coordonnées barycentriques (UNE SEULE FOIS)
    	float bary_v = (d11 * d20 - d01 * d21) / denom;
    	float bary_w = (d00 * d21 - d01 * d20) / denom;
    	float bary_u = 1.0f - bary_v - bary_w;

    	// Interpolate texture coordinates
    	float u_tex = bary_u * o->triangle.p0.uv.x +
					  bary_v * o->triangle.p1.uv.x +
					  bary_w * o->triangle.p2.uv.x;

    	float v_tex = bary_u * o->triangle.p0.uv.y +
					  bary_v * o->triangle.p1.uv.y +
					  bary_w * o->triangle.p2.uv.y;

    	unsigned int tex_color = sample_texture(scene, u_tex, v_tex);
    	ray->hit_rgb = texture_to_vec3(tex_color);

    	// Interpolate vertex normals (avec les VRAIES coordonnées barycentriques)
    	t_vec3 n0 = vec3_scale(o->triangle.p0.norm, bary_u);
    	t_vec3 n1 = vec3_scale(o->triangle.p1.norm, bary_v);
    	t_vec3 n2 = vec3_scale(o->triangle.p2.norm, bary_w);

    	ray->hit_normal = vec3_add(n0, vec3_add(n1, n2));
    	ray->hit_normal = unsafe_vec3_normalize(ray->hit_normal);

    	if (NORMAL_DEBUG)
    	{
    		ray->hit_rgb.x = ray->hit_normal.x * 0.5f + 0.5f;
    		ray->hit_rgb.y = ray->hit_normal.y * 0.5f + 0.5f;
    		ray->hit_rgb.z = ray->hit_normal.z * 0.5f + 0.5f;
    	}
    }
    else if (o->type == CYLINDER)
    {
       axis = o->cylinder.rot;
       to_hit = vec3_sub(hit_point, o->cylinder.pos);
       axis = vec3_scale(axis, vec3_dot(to_hit, axis));
       axis = vec3_add(o->cylinder.pos, axis);
       ray->hit_normal = vec3_sub(hit_point, axis);
       ray->hit_normal = unsafe_vec3_normalize(ray->hit_normal);
       ray->hit_rgb = o->cylinder.rgb;
    }
    ray->pos = hit_point;
}

t_object	*hit_sphere_bvh(t_ray *ray, t_sphere_bvh *bvh);

float	   hit_register(t_ray *ray, t_scene *scene, t_object **hit_object)
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
	hit_register_obj(ray, (*hit_object), scene);
	return ((*hit_object)->t);
}
