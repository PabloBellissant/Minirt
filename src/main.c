/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:00:29 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/20 18:53:16 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minirt.h"
#include "font_renderer.h"
#include "render.h"
#include <CL/cl.h>
#include <time.h>

void	register_unit_errors(void)
{
	register_lft_errors();
	register_mlxw_errors();
	register_frdr_errors();
	register_mlxui_errors();
	register_rt_errors();
}

int	setup_hooks(t_data *data);
int	init_ui(t_data *data);
int	init_graphics(t_data *data);

static inline int	try_parse_scene(t_data *data, char *rt_path)
{
	int	ret;

	data->scene.mlx = data->mlx;
	data->scene.skybox_tex = -1;
	errno = 0;
	if (parse_scene(rt_path, &data->scene, &data->cl) != 0)
	{
		ret = errno;
		kill_mlx(data->mlx);
		errno = ret;
		register_complex_err_msg(RT_E_MSG_PARSING, rt_path);
		return (error(pack_err(RT_ID, RT_E_PARSING), FL, LN, FC));
	}
	return (0);
}

static inline int	startup_minirt(t_data *data, char *rt_path)
{
	int	ret;

	ret = 0;
	if (init_graphics(data) == -1)
		ret = error(pack_err(RT_ID, RT_E_GRAPHICS), FL, LN, FC);
	else
	{
		ret = init_opencl(&data->cl, CL_DEVICE_TYPE_GPU);
		if (ret == 0)
			ret = try_parse_scene(data, rt_path);
		if (ret == 0)
			ret = init_ui(data);
		if (ret == 0)
		{
			data->buffers.addr = data->mlx->img.addr;
			data->buffers.accu = malloc(sizeof(t_vec3)
					* data->mlx->img.width * data->mlx->img.height);
			if (data->buffers.accu)
				setup_hooks(data);
		}
		else
			kill_mlx(data->mlx);
		free_data(data);
	}
	return (ret);
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
		ret = startup_minirt(&data, argv[1]);
	}
	print_errs();
	return (ret);
}
