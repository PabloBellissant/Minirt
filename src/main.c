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

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include "glb.h"
#include "parsing.h"
#include "init.h"

int	main(int argc, char **argv)
{
	t_scene	scene;
	t_data	mlx_data;

	if (argc < 2)
		return (1);
	if (parse_map(argv[1], &scene) != 0)
		return (2);
	if (init_graphics(&mlx_data) == -1)
		return (-1); // free
	(void) argv;
	return (0);
}

