/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:00:29 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/28 06:55:25 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minirt.h"
#include "threading.h"
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

void	free_scene(t_scene scene)
{
	free_phong(scene.phong);
	free_vector(&scene.lights);
	free_vector(&scene.objects);
}

void	free_data(t_data data)
{
	free_rast_env(data.font_env);
	free_scene(data.scene);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_queue	queue;

	(void)argv;
	if (argc < 2)
		return (1);
	ft_bzero(&data, sizeof(t_data));
	ft_bzero(&queue, sizeof(t_queue));
	data.queue = &queue;
	if (init_graphics(&data) == -1)
		return (2);
	if (parse_scene(argv[1], &data.scene) != 0)
		return (3); //free mlx;
	init_threads(data.queue);
	data.params.bvh_depth = data.scene.bvh.aabb_bvh->depth;
	loop_hook(&data);
	free_data(data);
	kill_threads(data.queue, NPROC);
	return (0);
}
