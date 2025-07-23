/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:37:35 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/24 00:42:25 by jaubry--         ###   ########lyon.fr   */
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

t_vec3	*phong_path(t_scene *scene, t_vec3 *normal, t_vec3 *col, t_vec3 *i_p);
void	fill_phong(t_ray *ray, t_scene *scene, t_vec3 *normal);

t_color	ray_path(t_ray *restrict ray, t_scene *scene)
{
	t_color		hit_color;
	//t_vec3		random_dir;
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
		fill_phong(&current_ray, scene, &normal);
		t_vec3	feur  = (t_vec3){hit_color.r * 255, hit_color.g * 255, hit_color.b * 255};
		t_vec3	color = (t_vec3){0, 0, 0};
		phong_path(scene, &normal, &feur, &color);
		//printf("ray (%f, %f, %f) color: R:%f G:%f B:%f\n", current_ray.pos.x, current_ray.pos.y, current_ray.pos.z, color.x, color.y, color.z);
		hit_color = (t_color){.r=color.x *255, .g=color.y *255, .b=color.z *255};
		add_colors(&result_color, &hit_color, 1 * addition);
		//vec3_random(&random_dir);
		//vec3_lerp(&current_ray.dir, &random_dir, 0.01f, &current_ray.dir);
		addition *= REFLECT;
		vec3_dot(&current_ray.dir, &normal, &temp);
		vec3_scale(&normal, 2 * temp);
		vec3_sub(&current_ray.dir, &normal, &current_ray.dir);
		vec3_unit(&current_ray.dir);
		/*
		*/
		bounce++;
	}
	return (result_color);
}

/*
	Will return the reflection direction
	needs the normalized normal and normalized direction to light
*/
static t_vec3	*reflection(const t_vec3 *normal, const t_vec3 *light_dir, t_vec3 *out)
{
	float	r;

	vec3_dot(light_dir, normal, &r);
	r *= 2;
	vec3_sub(normal, light_dir, out);
	return (vec3_scale(out, r));
}

void	fill_phong(t_ray *ray, t_scene *scene, t_vec3 *normal)
{
	size_t	m;

	vec3_sub(&scene->camera.pos, &ray->pos, &scene->phong.v);// get direction from hit to camera
	vec3_normalize(&scene->phong.v);// normalize vector

	m = 0;
	while (m < scene->lights.num_elements)
	{
		vec3_sub(&(((t_object *)scene->lights.data)[m].light.pos), &ray->pos, scene->phong.l + m);// direction to light
		vec3_normalize(scene->phong.l + m);// normalized direction to light

		reflection(normal, scene->phong.l + m, scene->phong.r + m);
		//vec3_normalize(scene->phong.r + m);// normalized reflection //maybe already normalized
		m++;
	}
}

//const t_vec3	k_a = (t_vec3){0.247f, 0.2f, 0.075f};
const t_vec3	k_d = (t_vec3){0.752f, 0.606f, 0.226f};
const t_vec3	k_s = (t_vec3){0.628f, 0.556f, 0.366f};
	
const t_vec3	i_a = (t_vec3){0.2f, 0.2f, 0.2f};
const t_vec3	i_d = (t_vec3){1.0f, 1.0f, 1.0f};
const t_vec3	i_s = (t_vec3){1.0f, 1.0f, 1.0f};

const float		alpha = 51.2f;

static t_vec3	*get_ambient(const t_vec3 *k_a, const t_vec3 *i_a, t_vec3 *out)
{
	return (vec3_mult(k_a, i_a, out));
}

static t_vec3	*get_diffuse(const t_vec3 *l_m, const t_vec3 *n, t_vec3 *out)
{
	float 	surface_faces_light;

	vec3_dot(l_m, n, &surface_faces_light);
	if (surface_faces_light > 0)
	{
		*out = (t_vec3){0, 0, 0};
		return (out);
	}
	vec3_mult(&k_d, &i_d, out);
	return(vec3_scale(out, surface_faces_light));
}

static t_vec3	*get_specular(const t_vec3 *r_m, const t_vec3 *v, t_vec3 *out)
{
	float 	surface_faces_camera;

	vec3_dot(r_m, v, &surface_faces_camera);
	if (surface_faces_camera > 0)
	{
		*out = (t_vec3){0, 0, 0};
		return (out);
	}
	vec3_mult(&k_s, &i_s, out);
	surface_faces_camera = powf(surface_faces_camera, alpha);
	return(vec3_scale(out, surface_faces_camera));
}

t_vec3	*phong_path(t_scene *scene, t_vec3 *normal, t_vec3 *col, t_vec3 *i_p)
{
	t_vec3	ambient;
	t_vec3	diffuse_m;
	t_vec3	specular_m;
	size_t	m;

	get_ambient(col, &i_a, &ambient);
	m = 0;
	while (m < scene->lights.num_elements)
	{
		get_diffuse(scene->phong.l + m, normal, &diffuse_m);
		get_specular(scene->phong.r + m, &(scene->phong.v), &specular_m);
		vec3_add(&diffuse_m, &specular_m, i_p);
		m++;
	}
	return (vec3_add(&ambient, i_p, i_p));
}
