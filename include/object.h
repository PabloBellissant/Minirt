/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 04:43:56 by jaubry--          #+#    #+#             */
/*   Updated: 2025/09/08 22:51:45 by jaubry--         ###   ########.fr       */
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
	t_vec3	tangent;
	t_vec3	bitangent;
}			t_plane;

typedef struct s_cylinder
{
	t_rgb	rgb;
	t_vec3	pos;
	t_vec3	rot;
	float	radius;
	float	diameter;
	float	height;
}			t_cylinder;

typedef struct s_vertex
{
	t_vec3	pos;
	union
	{
		struct
		{
			float	u;
			float	v;
		};
		t_vec2	uv;
	};
	t_vec3		norm;
}	t_vertex;

typedef struct s_triangle
{
	t_vertex	p0;
	t_vertex	p1;
	t_vertex	p2;
	t_vec3		edge_p1p0;
	t_vec3		edge_p2p0;
	t_rgb		rgb;
}	t_triangle;

typedef struct s_mat
{
	char	*name;
	float	ns;
	t_vec3	ka;
	t_vec3	kd;
	t_vec3	ks;
	t_vec3	ke;
	float	opacity;
	int		kd_id;
	int		normal_id;
	int		roughness_id;
	int		ambient_id;
	int		opacity_id;
	float	ni;
	float	pr;
}	t_mat;

typedef struct s_ray	t_ray;

typedef struct s_object
{
	char			*name;
	int				mat_id;
	t_object_type	type;
	int				(*f)(t_ray *, t_object *, float *);
	float			t;
	union
	{
		t_light		light;
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_triangle	triangle;
	};
}					t_object;

#endif// OBJECT_H
