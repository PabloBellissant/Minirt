/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:00:29 by pabellis          #+#    #+#             */
/*   Updated: 2026/01/20 18:21:59 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minirt.h"
#include "font_renderer.h"
#include "render.h"
#include <CL/cl.h>
#include <time.h>

void	free_ttf(t_ttf_font *font);

void	free_textures(t_vector *vec)
{
	size_t		i;
	t_texture	*texture;

	texture = vec->data;
	i = 0;
	while (i < vec->num_elements)
	{
		free(texture[i].addr);
		free(texture[i].name);
		++i;
	}
	free_vector(vec);
}

void	free_mats(t_vector *vec)
{
	size_t		i;
	t_mat		*mat;

	mat = vec->data;
	i = 0;
	while (i < vec->num_elements)
	{
		free(mat[i].name);
		++i;
	}
	free_vector(vec);
}

void	free_scene(t_scene *scene)
{
	free_vector(&scene->light);
	free_vector(&scene->objects);
	free(scene->planes_id);
	free_textures(&scene->texture);
	free_mats(&scene->mat);
	free_vector(&scene->mtl_list);
	free(scene->bvh.sphere_bvh);
	free(scene->bvh.triangle_bvh);
}

void	free_data(t_data *data)
{
	free_scene(&data->scene);
}

void	register_unit_errors(void)
{
	register_lft_errors();
	register_mlxw_errors();
	register_frdr_errors();
	register_rt_errors();
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		ret;

	srand(time(NULL));
	ret = 0;
	register_unit_errors();
	if (argc != 2)
	{
		register_complex_err_msg(RT_E_MSG_ARGC, argv[0], argc);
		ret = error(pack_err(RT_ID, RT_E_ARGC), FL, LN, FC);
	}
	else
	{
		ft_bzero(&data, sizeof(t_data));
		if (init_graphics(&data) == -1)
			ret = error(pack_err(RT_ID, RT_E_GRAPHICS), FL, LN, FC);
		else
		{
			if(init_opencl(&data.cl, CL_DEVICE_TYPE_GPU) != 0)
				return (1);
			data.scene.mlx = data.mlx;
			data.scene.skybox_tex = -1;
			errno = 0;
			if (parse_scene(argv[1], &data.scene, &data.cl) != 0)
			{
				ret = errno;
				kill_mlx(data.mlx);
				errno = ret;
				register_complex_err_msg(RT_E_MSG_PARSING, argv[1]);
				ret = error(pack_err(RT_ID, RT_E_PARSING), FL, LN, FC);
			}
			else
			{
				data.buffers.addr = data.mlx->img.addr;
				data.buffers.accu = malloc(sizeof(t_vec3) * WIDTH * HEIGHT);
				loop_hook(&data);
				free_data(&data);
			}
		}
	}
	cleanup_opencl(&data.cl);
	print_errs();
	return (ret);
}
