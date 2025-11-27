/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:00:29 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/13 18:43:15 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minirt.h"
#include "font_renderer.h"

void	free_ttf(t_ttf_font *font);

void	free_rast_env(t_rast_env *env)
{
	size_t	i;

	i = 0;
	while (i < env->text_num)
	{
		free_ttf(env->texts[i]->font);
		free(env->texts[i]);
		i++;
	}
	free_ttf(env->fps->font);
	free(env->fps);
	free(env);
}

void	free_phong(t_phong phong)
{
	ft_free(phong.l);
	ft_free(phong.r);
	ft_free(phong.d);
}

void	free_textures(t_vector *vec)
{
	size_t		i;
	t_texture	*texture;

	texture = vec->data;
	i = 0;
	while (i < vec->num_elements)
	{
		free(texture[i].pixels);
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
	free_phong(scene->phong);
	free_vector(&scene->lights);
	free_vector(&scene->objects);
	free(scene->planes);
	free_textures(&scene->texture);
	free_mats(&scene->mat);
	free(scene->bvh.bvh_pointer);
}

void	free_data(t_data *data)
{
	free_rast_env(data->font_env);
	free_scene(&data->scene);
	if (data->export_fd != -1)
		close(data->export_fd);
	//kill_mlx(data->mlx);
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
			data.scene.mlx = data.mlx;
			data.scene.skybox_tex = -1;
			data.export_fd = -1;
			errno = 0;
			if (parse_scene(argv[1], &data.scene) != 0)
			{
				ret = errno;
				kill_mlx(data.mlx);
				errno = ret;
				register_complex_err_msg(RT_E_MSG_PARSING, argv[1]);
				ret = error(pack_err(RT_ID, RT_E_PARSING), FL, LN, FC);
			}
			else
			{

				loop_hook(&data);
				free_data(&data);
			}
		}
	}
	print_errs();
	return (ret);
}
