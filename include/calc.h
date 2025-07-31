/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:50:50 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/31 21:14:20 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
# define CALC_H

# include "struct.h"

float	hit_register(t_ray *ray, t_vector *obj_vec, t_color *color, t_vec3 *normal);
t_color	ray_path(t_ray *ray, t_scene *scene);
int		hit_plane(t_ray *ray, t_object *o, float *t);
int		hit_sphere(t_ray *ray, t_object *o, float *t);
int		hit_cylinder(t_ray *ray, t_object *o, float *t);

#endif
