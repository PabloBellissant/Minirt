/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:18:56 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 05:17:40 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# ifndef DEBUG
#  define DEBUG 0
# endif//DEBUG

# ifndef WIDTH
#  define WIDTH 500
# endif//WIDTH

# ifndef HEIGHT
#  define HEIGHT 500
# endif//HEIGHT

# ifndef PERF
#  define PERF 0
# endif//PERF

# ifndef FULLSCREEN
#  define FULLSCREEN 0
# endif//FULLSCREEN

# ifndef WINDOWLESS
#  define WINDOWLESS 0
# endif//WINDOWLESS

# define BOUNCE_MAX 10
# define AUTHORS "'Aubry Richard Jaurel' And 'Bellissant Pablo'"
# define TITLE "Mini rt by Pabellis and Jaubry--"

# include <stdint.h>
# include "mlx_int.h"
# include "libft.h"
# include "parsing.h"
# include "vec3.h"
# include "render.h"

typedef struct s_keys
{
	bool	forward;
	bool	left;
	bool	right;
	bool	backward;
	bool	upward;
	bool	downward;
}			t_keys;

typedef struct s_mouse
{
	int		last_x;
	int		last_y;
	float	target_yaw;
	float	target_pitch;
	float	current_yaw;
	float	current_pitch;
}			t_mouse;

typedef struct s_data
{
	t_xvar		*mlx;
	t_win_list	*win;
	t_img		*img;
	int			*addr;
	t_keys		keys;
	t_mouse		mouse;
	bool		fullscreen;
	int			bits;
	int			line_len;
	int			endian;
	t_vec2i		screen;
	t_scene		scene;
}				t_data;

typedef struct MotifWmHints
{
	unsigned long	flags;
	unsigned long	functions;
	unsigned long	decorations;
	long			input_mode;
	unsigned long	status;
}					t_MotifWmHints;

int		init_graphics(t_data *data);
void	clear_scene(t_scene *scene);

int		loop_hook(t_data *mlx);
int		loop(t_data *mlx);

#endif//MINIRT_H
