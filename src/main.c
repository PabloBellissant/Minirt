/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:00:29 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/02 16:32:31 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "init.h"
#include "loop.h"
#include "time.h"

int	main(int argc, char **argv)
{
	t_data	mlx;

	if (argc < 2)
		return (1);
	srand(time(NULL));
	ft_bzero(&mlx, sizeof(t_data));
	if (init_graphics(&mlx) == -1)
		return (2);
	if (parse_map(argv[1], &mlx.scene) != 0)
		return (3); //free mlx;
	loop_hook(&mlx);
	(void) argv;
	return (0);
}

