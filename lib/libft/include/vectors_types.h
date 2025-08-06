/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 02:49:26 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/06 08:34:10 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_TYPES_H
# define VECTORS_TYPES_H

# include <stdint.h>

# define VEC2_LEN 2
# define VEC3_LEN 3
# define VEC4_LEN 4

typedef enum e_vec_idx
{
	VEC_X = 0,
	VEC_Y = 1,
	VEC_Z = 2,
	VEC_W = 3
}	t_vec_idx;

typedef struct s_vec2
{
	union
	{
		struct
		{
			float	x;
			float	y;
		};
		float		data[2];
	};
}					t_vec2;

typedef struct s_vec2i
{
	union
	{
		struct
		{
			int		x;
			int		y;
		};
		int			data[2];
	};
}					t_vec2i;

typedef struct s_vec3
{
	union
	{
		struct
		{
			float	x;
			float	y;
			float	z;
		};
		struct
		{
			float	r;
			float	g;
			float	b;
		};
		float		data[3];
	};
}					t_vec3;

typedef struct s_vec3i
{
	union
	{
		struct
		{
			int		x;
			int		y;
			int		z;
		};
		int			data[3];
	};
}					t_vec3i;

typedef struct s_vec4
{
	union
	{
		struct
		{
			float	x;
			float	y;
			float	z;
			float	w;
		};
		float		data[4];
	};
}					t_vec4;

typedef struct s_vec4i
{
	union
	{
		struct
		{
			int		x;
			int		y;
			int		z;
			int		w;
		};
		int			data[4];
	};
}					t_vec4i;

#endif//VECTORS_TYPES_H
