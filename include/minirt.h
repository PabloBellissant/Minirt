/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:18:56 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/28 20:04:27 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# ifndef DEBUG
#  define DEBUG 0
# endif//DEBUG

# ifndef MAX_WIDTH
#  define MAX_WIDTH 500
# endif//MAX_WIDTH

# ifndef MAX_HEIGHT
#  define MAX_HEIGHT 500
# endif//MAX_HEIGHT

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

# ifndef RESIZEABLE
#  define RESIZEABLE 0
# endif//RESIZEABLE

# define BOUNCE_MAX 10
# define AUTHORS "'Aubry Richard Jaurel' And 'Bellissant Pablo'"
# define TITLE "Mini rt by Pabellis and Jaubry--"

# include <stdint.h>
# include "mlx_int.h"
# include "libft.h"
# include "parsing.h"
# include "vectors.h"
# include "render.h"
# include "font_renderer.h"
# include "mlx_wrapper.h"

typedef struct s_keys
{
	bool	forward;
	bool	left;
	bool	right;
	bool	backward;
	bool	upward;
}			t_keys;

typedef struct s_mouse
{
	int		last_x;
	int		last_y;
	float	target_yaw;
	float	target_pitch;
	float	current_yaw;
	float	current_pitch;
	bool	warped;
}			t_mouse;

typedef struct s_data
{
	int			*addr;
	t_keys		keys;
	t_mouse		mouse;
	t_mlx		*mlx;
	t_vec2i		screen;
	t_scene		scene;
	t_rast_env	*font_env;
}				t_data;



int		init_graphics(t_data *data);
void	clear_scene(t_scene *scene);

int		loop_hook(t_data *mlx);
int		loop(t_data *mlx);

#endif//MINIRT_H
