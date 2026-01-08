/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:18:56 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/16 00:51:40 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

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

# define BOUNCE_MAX 2
# define REFRACT_MAX 5
# define AUTHORS "'Aubry Richard Jaurel' And 'Bellissant Pablo'"
# define TITLE "MiniRT Pabellis Jaubry--"

# define SUB_PIXEL_QUANTITY 1
# define TARGET_FPS 12
# define MIN_QUALITY 25

_Static_assert(SUB_PIXEL_QUANTITY > 0, "SUB_PIXEL_QUANTITY");
_Static_assert(TARGET_FPS > 0, "TARGET_FPS");
_Static_assert(MIN_QUALITY > 0, "MIN_QUALITY");

typedef struct s_keys
{
	bool	forward;
	bool	left;
	bool	right;
	bool	backward;
	bool	upward;
	bool	roll_left;
	bool	roll_right;
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
	bool	bvh_debug;
	bool	normal_debug;
	bool	smooth_shading;
	bool	quality_render;
	bool	exporting;
	bool	texture;
	bool	ambient;
	bool	normal_map;
}			t_params;

typedef struct s_buffers
{
	t_ray			*rays;
	t_hit			*hits;
	int				hits_count;
	unsigned int	*addr;
	t_vec3			*accu;
}			t_buffers;

typedef struct s_data
{
	t_buffers	buffers;
	t_params	params;
	t_keys		keys;
	t_mouse		mouse;
	t_mlx		*mlx;
	t_vec2i		screen;
	t_scene		scene;
	//t_rast_env	*font_env;
	int			export_fd;
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
