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

unsigned int sample_texture(t_texture *texture, float u, float v);
t_vec3 texture_to_vec3(unsigned int color);
#include "minirt.h"

float fast_atan2f(float y, float x)
{
	float	r;
	float	angle;
	float	abs_y;

	abs_y = fabsf(y) + 1e-10f;
	if (x < 0.0f)
	{
		r = (x + abs_y) / (abs_y - x);
		angle = 3.0f * M_PIf / 4.0f;
	}
	else
	{
		r = (x - abs_y) / (x + abs_y);
		angle = M_PIf / 4.0f;
	}
	angle += (0.1963f * r * r - 0.9817f) * r;
	if (y < 0.0f)
		return (-angle);
	return (angle);
}

t_rgb	draw_skybox(t_scene *scene, t_vec3 *dir)
{
	float	u;
	float	v;

	if (!scene->skybox)
		return (rgb(0, 0, 0));
	u = 0.5f + fast_atan2f(dir->z, dir->x) / (2.0f * M_PIf);
	v = 0.5f - asinf(dir->y) / M_PIf;
	return (texture_to_vec3(sample_texture(scene->skybox, u, v)));
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


t_rgb_int	ray_path(t_ray *ray, t_data *data, t_object **hit_object)
{
	float	hit_distance;
	t_rgb	color;
	float	reflect;
	static int o = 0;

	hit_distance = hit_register(ray, data, hit_object);
	if (hit_distance <= 0)
		return (rgb_ftoi(draw_skybox(&data->scene, &ray->dir)));
	ray->hit_mat = &(*hit_object)->mat;
	fill_phong(ray, &data->scene);
	if (data->params.normal_debug)
		return (rgb_ftoi(ray->hit_rgb));
	else
		color = phong_path(data, ray);
	reflect = get_reflect(ray->dir, ray->hit_normal, ray->hit_roughness, ray->hit_mat->ks.r);
	if (o < BOUNCE_MAX && reflect > 0.01f)
	{
		++o;
		ray->dir = vec3_reflect(ray->dir, ray->hit_normal);
		color = rgb_lerp(color, rgb_itof(ray_path(ray, data, hit_object)), reflect);
		o = 0;
	}
	return (rgb_ftoi(color));
}

void	hit_register_obj(t_ray *restrict ray, t_object *restrict objects, t_params *params);

t_rgb_int	fake_path(t_ray *ray, t_data *data, t_object *hit_object)
{
	t_rgb_int	final_color = rgb_int(0, 0, 0);

	hit_object->f(ray, hit_object, &hit_object->t);
	hit_register_obj(ray, hit_object, &data->params);
	if ((final_color.r <= 200) && (final_color.g <= 100))
	{
		if (hit_object->t <= 0)
			return (rgb_ftoi(draw_skybox(&data->scene, &ray->dir)));
		ray->hit_mat = &hit_object->mat;
		fill_phong(ray, &data->scene);
		if (data->params.normal_debug)
			final_color = rgb_ftoi(ray->hit_rgb);
		else
			final_color = rgb_ftoi(phong_path(data, ray));
	}
	return (final_color);
}

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
