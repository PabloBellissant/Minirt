/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:00:29 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 05:11:52 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minirt.h"
#include "time.h"

int	main(int argc, char **argv)
{
	t_data	mlx;
	time_t	seed;

	(void)argv;
	if (argc < 2)
		return (1);
	seed = time(NULL);
	if (DEBUG)
		printf("SEED: '%zu'\n", seed);
	srand(seed);
	ft_bzero(&mlx, sizeof(t_data));
	if (init_graphics(&mlx) == -1)
		return (2);
	if (parse_scene(argv[1], &mlx.scene) != 0)
		return (3); //free mlx;
	loop_hook(&mlx);
	return (0);
}
