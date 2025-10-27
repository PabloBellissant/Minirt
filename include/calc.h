/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 07:15:58 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/13 02:22:01 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
# define CALC_H

# include "object.h"
# include "render.h"

# define EPSILON 1e-3f
# define M_PIf 3.14159265358979323846f

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

t_rgb_int	ray_path(t_ray *ray, t_data *data, t_object **hit_object);
float		hit_register(t_ray *ray, t_data *data, t_object **hit_object);
t_object	*hit_reg_plane(t_ray *ray, t_scene *scene, float t_min);
int			hit_sphere(t_ray *ray, t_object *o, float *t);
int			hit_cylinder(t_ray *ray, t_object *o, float *t);
int			hit_plane(t_ray *restrict ray, t_object *restrict o, float *t);
int			hit_triangle(t_ray *ray, t_object *o, float *t);
void		calc_bvh_bound(t_camera *cam, t_bound *bound, t_bvh_main *bvh, int mode);
int			imax(int a, int b);
int			imin(int a, int b);
int			solve_quadratic(t_quadratic *q);

#endif
