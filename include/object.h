/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 04:43:56 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 14:22:47 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H
# include "vectors.h"
# include "colors.h"
# include "parsing.h"
# include <CL/cl.h>

typedef cl_float3		t_cl_rgb3;

typedef struct s_light
{
	t_cl_rgb3	rgb;
	cl_float3	pos;
}				t_light;

typedef struct s_texture_data
{
	int	index;
	int	offset;
	int	width;
	int	height;
	int	channels;
}		t_texture_data;

typedef struct s_mat
{
	char				*name;
	cl_float			ns;
	cl_float3			kd;
	cl_float3			ks;
	cl_float3			ke;
	cl_float			opacity;
	t_texture_data		kd_id;
	t_texture_data		normal_id;
	t_texture_data		roughness_id;
	t_texture_data		ambient_id;
	t_texture_data		opacity_id;
	t_texture_data		metalness_id;
	cl_float			ni;
}	t_mat;

typedef struct s_sphere
{
	union
	{
		t_vec3	pos;
		t_vec3	centroid;
	};
	union
	{
		float	radius;
		float	r;
	};
	union
	{
		float	diameter;
		float	d;
	};
	int			mat;
}			t_sphere;

typedef struct s_plane
{
	t_vec3	pos;
	t_vec3	normal;
	t_vec3	tangent;
	t_vec3	bitangent;
	int		mat;
	float	texture_scaling;
}			t_plane;

typedef struct s_vertex
{
	cl_float3		pos;
	union
	{
		struct
		{
			float	u;
			float	v;
		};
		cl_float2	uv;
	};
	cl_float3		norm;
}	t_vertex;

typedef struct s_triangle
{
	t_vec3			centroid;
	t_vertex		p0;
	t_vertex		p1;
	t_vertex		p2;
	cl_float3		edge_p1p0;
	cl_float3		edge_p2p0;
	int				mat;
	cl_float		d00;
	cl_float		d01;
	cl_float		d11;
	cl_float		denom;
}	t_triangle;

typedef struct s_mesh
{
	t_vec3		pos;
	t_vec3		centroid;
	t_vec3		rot;
	t_vec3		scale;
	char		*path;
	size_t		offset;
	size_t		triangle_count;
}	t_mesh;

typedef struct s_ray	t_ray;

typedef struct s_object
{
	char			*name;
	int				mat_id;
	int				object_id;
	t_object_type	type;
	union
	{
		char		mem;
		struct
		{
			union
			{
				t_vec3	centroid;
				t_vec3	pos;
			};
		};
		t_light		light;
		t_sphere	sphere;
		t_plane		plane;
		t_triangle	triangle;
	};
}					t_object;

#endif// OBJECT_H
