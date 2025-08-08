/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 04:43:56 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/06 09:22:08 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H
# include "vectors.h"
# include "colors.h"
# include "parsing.h"

typedef struct s_ambient
{
	float	ratio;
	t_rgb	rgb;
}			t_ambient;

typedef struct s_light
{
	float	brightness;
	t_rgb	rgb;
	t_vec3	pos;
}			t_light;

typedef struct s_sphere
{
	t_rgb	rgb;
	t_vec3	pos;
	float	diameter;
	float	radius_squared;
}			t_sphere;

typedef struct s_plane
{
	t_rgb	rgb;
	t_vec3	pos;
	t_vec3	normal;
}			t_plane;

typedef struct s_cylinder
{
	t_rgb	rgb;
	t_vec3	pos;
	t_vec3	rot;
	float	diameter;
	float	height;
}			t_cylinder;

typedef struct s_ray	t_ray;

typedef struct s_object
{
	char			*name;
	t_object_type	type;
	int				(*f)(t_ray *, t_object *, float *);
	float			t;
	union
	{
		t_light		light;
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	};
}					t_object;

#endif// OBJECT_H