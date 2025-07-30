/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:18:56 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/30 18:50:34 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdint.h>
# include "mlx_int.h"
# include "libft.h"
# include "parsing.h"

typedef struct s_keys
{
	bool	forward;
	bool	left;
	bool	right;
	bool	backward;
	bool	upward;
	bool	downward;
}	t_keys;

typedef struct s_mouse
{
	int		last_x;
	int		last_y;
	float target_yaw;
    float target_pitch;
    float current_yaw;
    float current_pitch;
}	t_mouse;

typedef union u_color
{
	struct
	{
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
		uint8_t	a;
	};
	uint32_t	rgb;
}	t_color;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

t_vec3	*get_real_ratio(const t_color *color, const float ratio, t_vec3 *rgb);

typedef union s_vec4
{
	struct
	{
		float	x;
		float	y;
		float	z;
		float	w;
	};
	float	global[4];
}	t_vec4;

typedef struct s_vertex
{
	t_vec3	pos;
	float	u;
	float	v;
}	t_vertex;

typedef struct s_triangle
{
	t_color		color;
	t_vertex	p0;
	t_vertex	p1;
	t_vertex	p2;
	t_vec3		normal;
}	t_triangle;

typedef struct	s_ambient
{
	float	ratio;
	t_color	color;
	t_vec3	col;
}	t_ambient;

typedef struct	s_camera
{
	t_vec3	pos;
	t_vec3	rot;
	int		fov;
}	t_camera;

typedef struct	s_light
{
	float	brightness;
	t_color	color;
	t_vec3	col;
	t_vec3	pos;
}	t_light;

typedef struct	s_sphere
{
	t_color	color;
	t_vec3	pos;
	float	diameter;
	float	radius_squared;
}	t_sphere;

typedef struct	s_plane
{
	t_color	color;
	t_vec3	pos;
	t_vec3	normal;
}	t_plane;

typedef struct	s_cylinder
{
	t_color	color;
	t_vec3	pos;
	t_vec3	rot;
	float	diameter;
	float	height;
}	t_cylinder;

typedef struct	s_obj
{
	t_vec3		pos;
	t_vec4		rot;
	t_vec3		scale;
	int			vertex_count;
	t_vertex	*vertex;
	// int			triangle_count;
	// t_triangle	*triangles;
}	t_obj;

typedef struct	s_ray
{
	t_vec3	pos;
	t_vec3	dir;
}	t_ray;

typedef struct	s_object
{
	char			*name;
	t_object_type	type;
	int				(*f)(t_ray *, t_object *, float *);
	union
	{
		t_light		light;
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_triangle	triangle;
	};
}	t_object;

typedef struct s_bvh	t_bvh;

typedef struct s_phong
{
	t_vec3	*l;//LIGHTS
	t_vec3	*r;//LIGHTS
	t_vec3	*d;//LIGHTS color
	t_vec3	v;
}	t_phong;

typedef struct	s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	char		*name;
	t_vector	objects;
	t_vector	lights;
	t_phong		phong;
	t_bvh		*bvh;
}	t_scene;

typedef struct	s_vec2i
{
	int	x;
	int	y;
}	t_vec2i;

typedef struct s_data
{
	t_xvar		*mlx;
	t_win_list	*win;
	t_img		*img;
	int			*addr;
	t_keys		keys;
	t_mouse		mouse;
	int			bits;
	int			line_len;
	int			endian;
	t_vec2i		screen;
	t_scene		scene;
}	t_data;

#endif


// 2317332
//
