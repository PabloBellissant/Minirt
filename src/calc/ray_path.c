/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:37:35 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/07 09:46:31 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "calc.h"
#include "vectors.h"

t_vec3		phong_path(t_data *data, t_ray *ray);
static void	fill_phong(t_ray *ray, t_scene *scene);

#define OFFSET 0.001f

t_rgb	sample_texture(t_texture *texture_list, int id, float u, float v);
t_vec3 texture_to_vec3(unsigned int color);
#include "minirt.h"

t_rgb	draw_skybox(t_scene *scene, t_vec3 *dir)
{
	float	u;
	float	v;

	if (scene->skybox_tex == -1)
		return (rgb(0, 0, 0));
	u = 0.5f + atan2f(dir->z, dir->x) / (2.0f * M_PIf);
	v = 0.5f + asinf(dir->y) / M_PIf;
	return (sample_texture(scene->texture.data, scene->skybox_tex, u, v));
}

t_vec3 vec3_reflect(t_vec3 ray, t_vec3 normal)
{
	t_vec3 scaled_normal = vec3_scale(normal, 2 * vec3_dot(ray, normal));
	return (vec3_sub(ray, scaled_normal));
}

t_vec3	vec3_neg(t_vec3 v)
{
	t_vec3	res;

	res.x = -v.x;
	res.y = -v.y;
	res.z = -v.z;
	return (res);
}

static inline t_vec3	rgb3_lerp(const t_vec3 a, const t_vec3 b, const t_vec3 t)
{
	return ((t_vec3){{
				a.x * (1.0f - t.x) + b.x * t.x,
				a.y * (1.0f - t.y) + b.y * t.y,
				a.z * (1.0f - t.z) + b.z * t.z
			}});
}

t_vec3 get_reflect(t_vec3 ray_dir, t_vec3 normal, float roughness, t_vec3 F0)
{
	t_vec3	fresnel;
	float	cos_theta;
	float	glossy_factor;
	t_vec3	specular;

	cos_theta = fabsf(vec3_dot(ray_dir, normal));
	fresnel = vec3_scale(vec3_sub(vec3(1, 1, 1), F0), powf(1.0f - cos_theta, 5.0f));
	fresnel = vec3_add(F0, fresnel);
	glossy_factor = 1.0f - 0.9f * roughness * roughness;
	specular = vec3_scale(fresnel, glossy_factor);
	return (specular);
}


t_vec3 vec3_refract(t_vec3 ray_dir, t_vec3 normal, float eta)
{
	float cosi = -vec3_dot(ray_dir, normal);
	float cost2 = 1.0f - eta * eta * (1.0f - cosi * cosi);
	if (cost2 < 0.0f)
		return (ray_dir);
	float cost = sqrtf(cost2);

	t_vec3 refr_dir = vec3_add(
		vec3_scale(ray_dir, eta),
		vec3_scale(normal, eta * cosi - cost)
	);
	return (vec3_normalize(refr_dir));
}

void	handle_reflect(t_ray *ray, t_data *data, t_rgb *color)
{
	static int	reflect_count = 0;
	t_object	*hit_object;
	t_vec3		reflect;

	if (reflect_count < BOUNCE_MAX)
	{
		reflect_count++;
		reflect = get_reflect(ray->dir, ray->hit_normal, ray->hit_roughness, ray->hit_mat->ks);
		ray->dir = vec3_reflect(ray->dir, ray->hit_normal);
		ray->pos = vec3_add(ray->pos, vec3_scale(ray->dir, EPSILON));
		*color = rgb3_lerp(*color, ray_path(ray, data, &hit_object), reflect);
		reflect_count--;
	}
}

t_object	*hit_register(t_ray *ray, t_data *data);
void		apply_mat(t_ray *restrict ray, t_object *restrict o, t_params *params, t_data *data);

t_object	*get_next_triangle(t_ray *ray, t_data *data, t_object *actual)
{
	t_object	*object;

	object = hit_register(ray, data);
	if (!object)
		return (actual);
	apply_mat(ray, object, &data->params, data);
	return (object);
}

float	get_cylinder_t_out(t_ray *ray, t_object *o);
float	get_sphere_t_out(t_ray *ray, t_object *o);

t_ray	*pass_through_sphere(t_ray *ray, t_object *obj)
{
	float	t_out;

	ray->dir = vec3_refract(ray->dir, ray->hit_normal, 1.0f / ray->hit_mat->ni);
	t_out = get_sphere_t_out(ray, obj);
	ray->pos = vec3_add(ray->pos, vec3_scale(ray->dir, t_out + EPSILON));
	ray->hit_normal = vec3_normalize(vec3_sub(obj->sphere.pos, ray->pos));
	ray->dir = vec3_refract(ray->dir, ray->hit_normal, ray->hit_mat->ni / 1.0f);
	return (ray);
}

t_ray	*pass_through_plane(t_ray *ray, t_object *obj)
{
	ray->pos = vec3_add(ray->pos, vec3_scale(obj->plane.normal, -EPSILON));
	return (ray);
}

t_ray	*pass_through_cylinder(t_ray *ray, t_object *obj)
{
	(void) ray;
	(void) obj;
	return (ray);
}

t_ray	*pass_through_triangle(t_ray *ray, t_data *data, t_object *obj)
{
	t_object	*next;
	t_ray		copy;

	copy = *ray;
	ray->dir = vec3_refract(ray->dir, ray->hit_normal, 1.0f / ray->hit_mat->ni);
	next = get_next_triangle(ray, data, obj);
	if (obj->mat_id != next->mat_id)
	{
		*ray = copy;
		ray->pos = vec3_add(ray->pos, vec3_scale(ray->dir, EPSILON));
		return (ray);
	}
	ray->pos = vec3_add(ray->pos, vec3_scale(ray->dir, EPSILON));
	ray->hit_normal = vec3_neg(ray->hit_normal);
	ray->dir = vec3_refract(ray->dir, ray->hit_normal, ray->hit_mat->ni / 1.0f);
	return (ray);
}

t_ray	*pass_through(t_ray *ray, t_object *obj, t_data *data)
{
	if (obj->type == SPHERE)
		return (pass_through_sphere(ray, obj));
	if (obj->type == PLANE)
		return (pass_through_plane(ray, obj));
	if (obj->type == TRIANGLE)
		return (pass_through_triangle(ray, data, obj));
	if (obj->type == CYLINDER)
		return (pass_through_cylinder(ray, obj));
	return (ray);
}

float	pass_through_no_refract(t_ray *ray, t_object *obj)
{
	float	t_out;

	if (obj->type == SPHERE)
		t_out = get_sphere_t_out(ray, obj);
	else if (obj->type == CYLINDER)
		t_out = get_cylinder_t_out(ray, obj);
	else
		t_out = 0;
	ray->pos = vec3_add(ray->pos, vec3_scale(ray->dir, t_out + EPSILON));
	return (t_out);
}

void	handle_refract(t_ray ray, t_data *data, t_rgb *color, t_object *obj)
{
	static int	refract_count = 0;
	t_object	*hit_object;
	float		opacity;

	if (refract_count < REFRACT_MAX && ray.hit_opacity < 0.99f)
	{
		opacity = ray.hit_opacity;
		++refract_count;
		pass_through(&ray, obj, data);
		*color = rgb_lerp(ray_path(&ray, data, &hit_object), *color, opacity);
		refract_count = 0;
	}
}


void	apply_mat(t_ray *restrict ray, t_object *restrict o, t_params *params, t_data *data);

t_rgb	ray_path(t_ray *ray, t_data *data, t_object **hit_object)
{
	t_rgb	color;

	*hit_object = hit_register(ray, data);
	if (!*hit_object)
		return (draw_skybox(&data->scene, &ray->dir));
	apply_mat(ray, (*hit_object), &data->params, data);
	if (data->params.normal_debug)
		return (rgb_add_scalar(rgb_scale(ray->hit_normal, 0.5f), 0.5f));
	ray->hit_mat = get_vector_value(&data->scene.mat, (*hit_object)->mat_id);
	fill_phong(ray, &data->scene);
	color = phong_path(data, ray);
	handle_refract(*ray, data, &color, *hit_object);
	handle_reflect(ray, data, &color);
	return (color);
}

// t_rgb	ray_path(t_ray *ray, t_data *data, t_object **hit_object)
// {
// 	float	hit_distance;
// 	t_rgb	color;
//
// 	hit_distance = hit_register(ray, data, hit_object);
// 	if (hit_distance <= 0)
// 		return (draw_skybox(&data->scene, &ray->dir));
// 	if (data->params.normal_debug)
// 		return (ray->hit_rgb);
// 	ray->hit_mat = get_vector_value(&data->scene.mat, (*hit_object)->mat_id);
// 	fill_phong(ray, &data->scene);
// 	color = phong_path(data, ray);
// 	handle_refract(*ray, data, &color, *hit_object);
// 	handle_reflect(ray, data, &color);
// 	return (color);
// }


/*
	Will return the reflection direction
	needs the normalized normal and normalized direction to light
*/

static t_vec3	reflection(const t_vec3 normal, const t_vec3 light_dir)
{
	const float	r = vec3_dot(light_dir, normal) * 2;

	return (vec3_sub(vec3_scale(normal, r), light_dir));
}

static void	fill_phong(t_ray *ray, t_scene *scene)
{
	t_object	*lights;
	size_t		m;

	scene->phong.v = vec3_normalize(vec3_sub(scene->camera.pos, ray->pos));
	m = 0;
	lights = (t_object *)scene->lights.data;
	while (m < scene->lights.num_elements)
	{
		scene->phong.d[m] = lights[m].light.rgb;
		scene->phong.l[m] = vec3_normalize(vec3_sub(lights[m].light.pos,
					ray->pos));
		scene->phong.r[m] = reflection(ray->hit_normal, scene->phong.l[m]);
		m++;
	}
}
