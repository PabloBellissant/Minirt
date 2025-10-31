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

#include <float.h>
#define OFFSET 0.001f

inline static void	light_hit_register_data(t_ray *ray,
		t_light *light, float t_min)
{
	t_vec3	hit_dir;
	t_vec3	hit_point;

	hit_dir = vec3_scale(ray->dir, t_min);
	hit_point = vec3_add(ray->pos, hit_dir);
	ray->hit_normal = vec3_normalize(vec3_sub(hit_point, light->pos));
	ray->hit_rgb = light->rgb;
	ray->pos = hit_point;
}

inline static int	light_intersect(t_ray *ray, t_light *light, float *t)
{
	const t_vec3	oc = vec3_sub(ray->pos, light->pos);
	const float		a = vec3_dot(ray->dir, ray->dir);
	const float		b = vec3_dot(oc, ray->dir);
	float			temp;

	temp = b * b - a * vec3_dot(oc, oc);
	if (temp < 0)
		return (0);
	temp = sqrtf(temp);
	*t = (-b - temp) / a;
	if (*t > OFFSET)
		return (1);
	*t = (-b + temp) / a;
	if (*t > OFFSET)
		return (1);
	return (0);
}


float	light_hit_register(t_ray *ray, t_scene *scene)
{
	t_object	*lights;
	float		t_min = FLT_MAX;
	float		t_current;
	int			hit_light_idx = -1;
	size_t		i = 0;

	lights = (t_object *)scene->lights.data;
	while (i < scene->lights.num_elements)
	{
		if (light_intersect(ray, &(lights[i].light), &t_current))
		{
			if (t_current < t_min)
			{
				t_min = t_current;
				hit_light_idx = (int)i;
			}
		}
		++i;
	}
	if (hit_light_idx == -1)
		return (0);
	light_hit_register_data(ray, &(lights[hit_light_idx].light), t_min);
	return (t_min);
}

unsigned int sample_texture_coordinates(t_texture *texture, float u, float v);
t_vec3 texture_to_vec3(unsigned int color);
#include "minirt.h"

t_rgb	draw_skybox(t_scene *scene, t_vec3 *dir)
{
	float	u;
	float	v;

	if (!scene->skybox)
		return (rgb(0, 0, 0));
	u = 0.5f + atan2f(dir->z, dir->x) / (2.0f * M_PIf);
	v = 0.5f - asinf(dir->y) / M_PIf;
	return (texture_to_vec3(sample_texture_coordinates(scene->skybox, u, v)));
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
//
// float	get_reflect(t_vec3 ray_dir, t_vec3 normal, t_vec3 ks, float roughness)
// {
// 	float cos_theta;
// 	float factor;
// 	t_vec3 reflect;
//
// 	cos_theta = fabsf(vec3_dot(ray_dir, normal));;
// 	factor = powf(1.0f - cos_theta, 5.0f);
// 	t_vec3 one_minus_ks = vec3_sub(vec3(1.0f,1.0f,1.0f), ks);
// 	reflect = vec3_add(ks, vec3_scale(one_minus_ks, factor));
// 	return (reflect.x * (1.0f - roughness));
// }

float get_reflect(t_vec3 ray_dir, t_vec3 normal, float roughness, float F0)
{
	float cos_theta = fabsf(vec3_dot(ray_dir, normal));
	float fresnel = F0 + (1.0f - F0) * powf(1.0f - cos_theta, 5.0f);
	float glossy = fresnel * (1.0f - 0.9f * roughness * roughness);
	return glossy;
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

t_rgb	handle_reflect(t_ray *ray, t_data *data, t_rgb *color)
{
	static int	reflect_count = 0;
	t_object	*hit_object;
	float		reflect;
	t_rgb		result;


	reflect = get_reflect(ray->dir, ray->hit_normal, ray->hit_roughness, ray->hit_mat->ks.r);
	if (reflect_count < BOUNCE_MAX && reflect > 0.01f)
	{
		++reflect_count;
		ray->dir = vec3_reflect(ray->dir, ray->hit_normal);
		result = rgb_lerp(*color, rgb_itof(ray_path(ray, data, &hit_object)), reflect);
		reflect_count = 0;
		return (result);
	}
	return (*color);
}

float	get_cylinder_t_out(t_ray *ray, t_object *o);
float	get_sphere_t_out(t_ray *ray, t_object *o);
#define refraction 1.03f
t_rgb	handle_refract(t_ray *ray, t_data *data, t_rgb *color, t_object *obj)
{
	static int	refract_count = 0;
	t_object	*hit_object;
	float		refract;
	float		t_out;
	float		transparency;
	t_rgb		result;

	transparency = 1.0f - ray->hit_opacity;
	if (refract_count < BOUNCE_MAX && transparency > 0)
	{
		++refract_count;
		if (obj->type != SPHERE && obj->type != CYLINDER)
			ray->pos = vec3_add(ray->pos, vec3_scale(vec3_neg(ray->hit_normal), EPSILON));
		else
		{
			refract = 1.0f / refraction;
			ray->dir = vec3_refract(ray->dir, ray->hit_normal, refract);
			if (obj->type == SPHERE)
				t_out = get_sphere_t_out(ray, obj);
			else
				t_out = get_cylinder_t_out(ray, obj);
			ray->pos = vec3_add(ray->pos, vec3_scale(ray->dir, t_out + EPSILON));
			ray->hit_normal = vec3_normalize(vec3_sub(obj->sphere.pos, ray->pos));
			refract = refraction / 1.0f;
			ray->dir = vec3_refract(ray->dir, ray->hit_normal, refract);
		}
		result = rgb_lerp(*color, rgb_itof(ray_path(ray, data, &hit_object)), transparency);
		refract_count = 0;
		return (result);
	}
	return (*color);
}

t_rgb_int	ray_path(t_ray *ray, t_data *data, t_object **hit_object)
{
	float	hit_distance;
	t_rgb	color;
	t_vec3	pos;
	t_vec3	dir;

	hit_distance = hit_register(ray, data, hit_object);
	if (hit_distance <= 0)
		return (rgb_ftoi(draw_skybox(&data->scene, &ray->dir)));
	if (data->params.normal_debug)
		return (rgb_ftoi(ray->hit_rgb));
	ray->hit_mat = &(*hit_object)->mat;
	fill_phong(ray, &data->scene);
	color = phong_path(data, ray);
	pos = ray->pos;
	dir = ray->dir;
	color = handle_refract(ray, data, &color, *hit_object);
	ray->pos = pos;
	ray->dir = dir;
	color = handle_reflect(ray, data, &color);
	return (rgb_ftoi(color));
}

void	hit_register_obj(t_ray *restrict ray, t_object *restrict objects, t_params *params);

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
