/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:18:56 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/16 01:19:02 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdint.h>
# include "mlx_int.h"
#include <threads.h>

typedef union u_color
{
	struct
	{
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
	};
	uint32_t	rgb;
}	t_color;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_vertex
{
	t_vec3	pos;
	float	u;
	float	v;
}	t_vertex;

typedef struct s_triangle
{
	t_vertex	p0;
	t_vertex	p1;
	t_vertex	p2;
	t_vec3		normal;
	double		roughness;
	double		metallic;
	t_color		color;
}	t_triangle;

typedef struct s_object
{
	t_vec3		translation;
	t_vec3		rotation;
	t_vec3		scale;
	char		*name;
	t_triangle	*triangles;
	int			triangle_count;
}	t_object;

typedef struct	s_scene
{
	char		*name;
	int			object_count;
	t_object	*objects;
}	t_scene;

typedef struct	s_ray
{
	t_vec3	pos;
	t_vec3	dir;
}	t_ray;

typedef struct	s_pos2
{
	int	dim_x;
	int	dim_y;
}	t_pos2;

typedef struct s_data
{
	t_xvar		*mlx;
	t_win_list	*win;
	t_img		*img;
	int			*addr;
	int			bits;
	int			line_len;
	int			endian;
	t_pos2		screen;
}	t_data;

#endif
