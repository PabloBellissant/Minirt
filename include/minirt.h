/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:18:56 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/09 02:39:52 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "mlx_wrapper.h"



# define BOUNCE_MAX 4
# define AUTHORS "'Aubry Richard Jaurel' And 'Bellissant Pablo'"
# define TITLE "Mini rt by Pabellis and Jaubry--"

# define TARGET_FPS 24
# define MIN_QUALITY 20;
# define MAX_SUBSAMPLING 3

# define M_PIf 3.14159265358979323846f

# include <stdint.h>
# include "xcerrcal.h"
# include "rt_xcerrcal.h"
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
	float	target_yaw;
	float	target_pitch;
	float	current_yaw;
	float	current_pitch;
}			t_mouse;

typedef struct s_params
{
	int		render_mode;
	int		bvh_depth;
	int		bvh_color_offset;
	int		supersampling_x;
	int		supersampling_y;
	bool	bvh_debug;
	bool	bound_debug;
	bool	supersampling_debug;
	bool	normal_debug;
	bool	smooth_shading;
	bool	texture;
	bool	quality_render;
}			t_params;

typedef struct	s_too_task
{
	t_data		*data;
	t_ray		ray;
	t_camera	cam;
	int			y;
}	t_to_task;

#include "threading.h"

typedef struct s_data
{
	int			*addr;
	t_params	params;
	t_keys		keys;
	t_mouse		mouse;
	t_mlx		*mlx;
	t_vec2i		screen;
	t_scene		scene;
	t_rast_env	*font_env;
	t_queue		*queue;
	t_to_task	to_task[HEIGHT];
	t_task		task[HEIGHT];
}				t_data;

typedef enum e_obj
{
	null = 0,
	mtllib,
	usemtl,
	vn,
	vt,
	v,
	f
}	t_obj;

int		init_graphics(t_data *data);
void	clear_scene(t_scene *scene);

int		loop_hook(t_data *mlx);
int		loop(t_data *mlx);

#endif//MINIRT_H
