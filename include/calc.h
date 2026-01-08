/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 07:15:58 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/11 19:49:12 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
# define CALC_H

# include "object.h"
# include "render.h"

# define EPSILON 1e-5f

typedef struct s_quadratic
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	t_min;
	float	t_max;
	float	oo;
	float	dd;
}	t_quadratic;

t_rgb		ray_path(t_ray *ray, t_data *data, t_object **hit_object);
t_object	*hit_reg_plane(t_ray *ray, t_scene *scene, float t_min);
t_object	*hit_register(t_ray *ray, t_scene *scene);
int			hit_sphere(t_ray *ray, t_object *o, float *t_in);
int			hit_cylinder(t_ray *ray, t_object *o, float *t);
int			hit_plane(t_ray *restrict ray, t_object *restrict o, float *t);
int			hit_triangle(t_ray *ray, t_object *o, float *t);
int			imax(int a, int b);
int			imin(int a, int b);
int			solve_quadratic(t_quadratic *q);

t_vec3		get_reflect(t_vec3 ray_dir, t_vec3 normal,
				float roughness, t_vec3 F0);
t_rgb		get_f0(float metalness, float ior, t_rgb ks);
t_vec3		vec3_reflect(t_vec3 ray, t_vec3 normal);

void		refract(t_vec3 *origin, t_vec3 *dir, t_hit *hit, float ni);

void		fill_uv_normal(t_vec3 hit_point, t_object *object,
				t_vec2 *uv, t_vec3 *norm);
void		fill_skybox_uv(const t_vec3 *dir, t_vec2 *uv);

t_vec3		vec3_rand(void);
t_vec3		vec3_rand_in_sphere(float sphere_radius);
t_vec3		random_point_in_triangle(t_triangle *triangle);
t_light		get_random_light(
				t_scene *scene, int total_lights, t_vec3 hit_point);
t_vec3		apply_normal_map(t_vec3 normal, t_vec3 nmap,
				t_vec3 tangent, t_vec3 bitangent);

#endif
