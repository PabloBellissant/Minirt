/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 02:54:43 by jaubry--          #+#    #+#             */
/*   Updated: 2025/08/07 01:40:36 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_TYPES_H
# define COLORS_TYPES_H

# include <stdint.h>
# include "vectors_types.h"

# define RGB_LEN 3
# define RGBA_LEN 4

typedef enum e_col_idx
{
	COL_R = 0,
	COL_G = 1,
	COL_B = 2,
	COL_A = 3
}	t_col_idx;

typedef t_vec3		t_rgb;

typedef struct s_rgb_int
{
	union
	{
		struct
		{
			uint8_t	b;
			uint8_t	g;
			uint8_t	r;
		};
		uint8_t		data[3];
		uint32_t	rgb;
	};
}					t_rgb_int;

typedef struct s_rgba
{
	union
	{
		struct
		{
			float	r;
			float	g;
			float	b;
			float	a;
		};
		float		data[4];
	};
}					t_rgba;

typedef struct s_rgba_int
{
	union
	{
		struct
		{
			uint8_t	r;
			uint8_t	g;
			uint8_t	b;
			uint8_t	a;
		};
		uint8_t		data[4];
		uint32_t	rgba;
	};
}					t_rgba_int;

static inline t_rgb	rgb(const float r, const float g, const float b)
{
	return ((t_rgb){{{r, g, b}}});
}

static inline t_rgba	rgba(const float r, const float g,
							const float b, const float a)
{
	return ((t_rgba){{{r, g, b, a}}});
}

static inline t_rgb_int	rgb_int(const uint8_t r, const uint8_t g,
							const uint8_t b)
{
	return ((t_rgb_int){{{b, g, r}}});
}

static inline t_rgba_int	rgba_int(const uint8_t r, const uint8_t g,
								const uint8_t b, const uint8_t a)
{
	return ((t_rgba_int){{{r, g, b, a}}});
}

#endif//COLORS_TYPES_H
