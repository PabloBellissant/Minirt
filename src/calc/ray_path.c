/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:37:35 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/30 08:39:54 by jaubry--         ###   ########lyon.fr   */
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

t_vec3	*phong_path(t_scene *scene, t_ray *ray, t_vec3 *normal, t_vec3 *col, t_vec3 *i_p);
void	fill_phong(t_ray *ray, t_scene *scene, t_vec3 *normal);

t_vec3	*vec3_clamp(t_vec3 *vec, float min, float max)
{
	float	*xyz[3];
	size_t	i;

	xyz[0] = &(vec->x);
	xyz[1] = &(vec->y);
	xyz[2] = &(vec->z);
	i = 0;
	while (i < 3)
	{
		if (*(xyz[i]) < min)
			*(xyz[i]) = min;
		else if (*(xyz[i]) > max)
			*(xyz[i]) = max;
		i++;
	}
	return (vec);
}

t_color	*vec3_to_color(const t_vec3 *vec, t_color *col)
{
	int	temp;

	temp = vec->x * 255;
	if (temp > 255)
		col->r = 255;
	else if (temp < 0)
		col->r = 0;
	else
		col->r = temp;
	temp = vec->y * 255;
	if (temp > 255)
		col->g = 255;
	else if (temp < 0)
		col->g = 0;
	else
		col->g = temp;
	temp = vec->z * 255;
	if (temp > 255)
		col->b = 255;
	else if (temp < 0)
		col->b = 0;
	else
		col->b = temp;
	return (col);
}


t_color ray_path(t_ray *ray, t_scene *scene)
{
	t_color	hit_color;
	t_vec3	normal;
	float	hit_result;

	hit_result = hit_register(ray, &scene->objects, &hit_color, &normal);
	if (hit_result == 0)
		return ((t_color){.rgb=0}); // Background color

	fill_phong(ray, scene, &normal);
	// Convert hit_color to [0,1] vector
	t_vec3	bounce_color_vec = {
		(float)hit_color.r / 255.0f,
		(float)hit_color.g / 255.0f,
		(float)hit_color.b / 255.0f
	};
	t_vec3	color_accumulator = {0, 0, 0};
	phong_path(scene, ray, &normal, &bounce_color_vec, &color_accumulator);
	vec3_clamp(&color_accumulator, 0.0f, 1.0f);

	t_color	final_color;
	vec3_to_color(&color_accumulator, &final_color);
	return (final_color);
}


static t_vec3	*get_real_ratio(const t_color *color, const float ratio, t_vec3 *rgb)
{
	rgb->x = (float)color->r / 255.0f;
	rgb->y = (float)color->g / 255.0f;
	rgb->z = (float)color->b / 255.0f;
	return (vec3_scale(rgb, ratio));
}


/*
	Will return the reflection direction
	needs the normalized normal and normalized direction to light
*/
static t_vec3	*reflection(const t_vec3 *normal, const t_vec3 *light_dir, t_vec3 *out)
{
	float	r;
	t_vec3	temp;

	vec3_dot(light_dir, normal, &r);
	r *= 2;
	temp = *normal;
	vec3_scale(&temp, r);
	return (vec3_sub(&temp, light_dir, out));
}

void	fill_phong(t_ray *ray, t_scene *scene, t_vec3 *normal)
{
	size_t	m;
	t_object	*lights;

	vec3_sub(&scene->camera.pos, &ray->pos, &scene->phong.v);// get direction from hit to camera
	vec3_normalize(&scene->phong.v);// normalize vector
	m = 0;
	lights = (t_object *)scene->lights.data;
	while (m < scene->lights.num_elements)
	{
		get_real_ratio(&(lights[m].light.color), lights[m].light.brightness, scene->phong.d + m);

		vec3_sub(&(lights[m].light.pos), &ray->pos, scene->phong.l + m);// direction to light
		vec3_normalize(scene->phong.l + m);// normalized direction to light

		reflection(normal, scene->phong.l + m, scene->phong.r + m);
		vec3_normalize(scene->phong.r + m);// normalized reflection //maybe already normalized
		m++;
	}
}

//const t_vec3	k_aa = (t_vec3){0.247f, 0.2f, 0.075f}; // object reflection
const t_vec3	k_d = (t_vec3){0.752f, 0.606f, 0.226f};// object diffuse
const t_vec3	k_s = (t_vec3){0.628f, 0.556f, 0.366f};// object specular
	
//const t_vec3	i_a = (t_vec3){0.2f, 0.2f, 0.2f}; // ambient light (RGB(uint8_t) * ratio(float))
//const t_vec3	i_d = (t_vec3){1.0f, 1.0f, 1.0f}; // lights color
const t_vec3	i_s = (t_vec3){1.0f, 1.0f, 1.0f};

const float		alpha = 55.2f;

static t_vec3	*get_ambient(const t_vec3 *k_a, const t_vec3 *i_a, t_vec3 *out)
{
	return (vec3_mult(k_a, i_a, out));
}

static t_vec3	*get_diffuse(const t_vec3 *l_m, const t_vec3 *i_d, const t_vec3 *n, t_vec3 *out)
{
	float 	surface_faces_light;

	vec3_dot(l_m, n, &surface_faces_light);
	if (surface_faces_light <= 0)
	{
		*out = (t_vec3){0, 0, 0};
		return (out);
	}
	vec3_mult(&k_d, i_d, out);
	return(vec3_scale(out, surface_faces_light));
}

static t_vec3	*get_specular(const t_vec3 *r_m, const t_vec3 *v, t_vec3 *out)
{
	float 	surface_faces_camera;

	vec3_dot(r_m, v, &surface_faces_camera);
	if (surface_faces_camera <= 0)
	{
		*out = (t_vec3){0, 0, 0};
		return (out);
	}
	vec3_mult(&k_s, &i_s, out);
	surface_faces_camera = powf(surface_faces_camera, alpha);
	return(vec3_scale(out, surface_faces_camera));
}

// Add this function to test if light is blocked
int is_light_blocked(t_scene *scene, t_vec3 *hit_point, t_vec3 *light_pos, t_vec3 *normal)
{
    t_ray shadow_ray;
    t_color dummy_color;
    t_vec3 dummy_normal;
    t_vec3 to_light;
    t_vec3 offset_point;
    float light_distance;
    float hit_distance;
    
    // Add shadow bias - offset the ray origin along the normal
    const float SHADOW_BIAS = 0.001f;  // Adjust this value as needed
    offset_point = *normal;
    vec3_scale(&offset_point, SHADOW_BIAS);
    vec3_add(hit_point, &offset_point, &offset_point);
    
    // Create ray from offset point to light
    shadow_ray.pos = offset_point;  // Use offset point instead of hit_point
    vec3_sub(light_pos, &offset_point, &to_light);
    light_distance = vec3_length(&to_light);
    vec3_normalize(&to_light);
    shadow_ray.dir = to_light;
    
    // Check if anything blocks the light
    hit_distance = hit_register(&shadow_ray, &scene->objects, &dummy_color, &dummy_normal);
    
    // If we hit something before reaching the light, it's blocked
    return (hit_distance > 0 && hit_distance < light_distance);
}


t_vec3	*phong_path(t_scene *scene, t_ray *ray, t_vec3 *normal, t_vec3 *col, t_vec3 *i_p)
{
	t_vec3	ambient;
	t_vec3	diffuse_m;
	t_vec3	specular_m;
	t_vec3	i_a;
	t_vec3	temp;
	size_t	m;

	get_real_ratio(&(scene->ambient.color), scene->ambient.ratio, &i_a);
	get_ambient(col, &i_a, &ambient);
	m = 0;
	while (m < scene->lights.num_elements)
	{
		if (is_light_blocked(scene, &ray->pos, &(((t_object *)(scene->lights.data))[m].light.pos), normal))
		{
			m++;
			continue; // Skip this light if blocked
		}
		get_diffuse(scene->phong.l + m, scene->phong.d + m, normal, &diffuse_m);
		get_specular(scene->phong.r + m, &(scene->phong.v), &specular_m);
		vec3_add(&diffuse_m, &specular_m, &temp);
		vec3_add(i_p, &temp, i_p);
		m++;
	}
	return (vec3_add(i_p, &ambient, i_p));
}
