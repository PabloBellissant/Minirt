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

typedef struct s_json	t_json;

typedef union u_color
{
	struct
	{
		uint8_t	a;
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
	};
	uint32_t	argb;
}	t_color;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_triangle
{
	t_vec3	p0;
	t_vec3	p1;
	t_vec3	p2;
	t_vec3	normal;
	t_color	color;
	double	roughness;
	double	metallic;
}	t_triangle;

typedef struct s_object
{
	t_triangle	*triangles;
	int			triangle_count;
	t_vec3		translation;
	t_vec3		rotation;
	t_vec3		scale;
	char		*name;
}	t_object;

typedef enum e_json_type
{
	JSON_NULL,
	JSON_BOOL,
	JSON_NUMBER,
	JSON_ARRAY,
	JSON_OBJECT,
	JSON_STRING
}	t_json_type;

typedef struct s_json
{
	char		*key;
	t_json_type	type;
	union
	{
		bool	boolean;
		double	number;
		char	*string;
		t_json	*child;
	};
	t_json		*next;
}	t_json;

#endif
