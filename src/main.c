/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:00:29 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/15 18:00:32 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "init.h"
#include "loop.h"
#include "threading.h"
#include "define.h"

# define SQUARE_SIZE 10

int function(void *arg)
{
	t_task_data	*task_data;
	t_data		*data;
	int			i;

	task_data = arg;
	data = task_data->data;
	i = 0;
	while (i < SCREEN_WIDTH)
	{
		data->addr[i + (task_data->i * SCREEN_WIDTH)] = 0xFFFFFF;
		usleep(1500);
		++i;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_scene	scene;
	t_data	mlx_data;

	if (argc < 2)
		return (1);
	if (init_graphics(&mlx_data) == -1)
		return (2);
	if (parse_map(argv[1], &scene) != 0)
		return (3); //free mlx;

	t_task	*task;
	t_task_data	*data;
	t_queue	queue;

	ft_bzero(&queue, sizeof(t_queue));
	queue.len = 0;
	queue.start = 0;
	init_threads(&queue);

	int i = 0;
	while (i < SCREEN_HEIGHT)
	{
		task = malloc(sizeof(t_task));
		data = malloc(sizeof(t_task_data));
		task->f = function;
		data->data = &mlx_data;
		data->i = i;
		task->data = data;
		enqueue(task, &queue);
		++i;
	}

	loop_hook(&mlx_data);
	(void) argv;
	return (0);
}

