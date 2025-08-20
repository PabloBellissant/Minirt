/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 17:50:50 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/07 09:38:09 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALC_H
# define CALC_H

# include "object.h"
# include "render.h"

t_rgb_int	ray_path(t_ray *ray, t_scene *scene);
float		hit_register(t_ray *restrict ray, t_scene *scene);
t_object	*hit_reg_plane(t_ray *ray, t_scene *scene, float t_min);
int			hit_sphere(t_ray *ray, t_object *o, float *t);
int			hit_cylinder(t_ray *ray, t_object *o, float *t);

#endif
