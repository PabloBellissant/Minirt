/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 01:18:56 by pabellis          #+#    #+#             */
/*   Updated: 2026/01/19 15:57:32 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdint.h>
# include "CL/cl.h"
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
}			t_params;

typedef struct s_buffers
{
	t_ray			*rays;
	t_hit			*hits;
	int				hits_count;
	unsigned int	*addr;
	t_vec3			*accu;
}			t_buffers;

typedef struct s_kernel
{
	cl_kernel	phong;
	cl_kernel	draw_accu;
	cl_kernel	pbr;
	cl_kernel	monte_carlo;
	cl_kernel	normal;
	cl_kernel	heat;
}	t_kernel;

typedef struct s_gpu_buffers
{
	cl_mem	accu;
	cl_mem	img;
}	t_gpu_buffers;

typedef struct s_opencl {
    cl_platform_id platform;
    cl_device_id device;
    cl_context context;
    cl_command_queue queue;
    cl_program program;
	t_kernel	kernel;
	t_gpu_buffers	bu;
    unsigned char *host_buffer;
}	t_opencl;

typedef struct s_data
{
	t_opencl	cl;
	t_buffers	buffers;
	t_params	params;
	t_keys		keys;
	t_mouse		mouse;
	t_mlx		*mlx;
	t_vec2i		screen;
	t_scene		scene;
}				t_data;

typedef struct s_kernel_def
{
	const char	*name;
	cl_kernel	*kernel;
}	t_kernel_def;

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
int		init_opencl(t_opencl *state, cl_device_type id);
void	 cleanup_opencl(t_opencl *state);
void	clear_scene(t_scene *scene);

int		loop_hook(t_data *mlx);
int		loop(t_data *mlx);

#endif//MINIRT_H
