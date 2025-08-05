/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:50:50 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 05:14:24 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
# define CALC_H

# include "object.h"
# include "render.h"

float	hit_register(t_ray *ray, t_vector *obj_vec);
t_color	ray_path(t_ray *ray, t_scene *scene);
int		hit_plane(t_ray *ray, t_object *o, float *t);
int		hit_sphere(t_ray *ray, t_object *o, float *t);
int		hit_cylinder(t_ray *ray, t_object *o, float *t);

#endif
