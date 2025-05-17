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

static int	fill_str(char *file_name);

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (1);
	if (fill_str(argv[1]) != 0)
		return (2);
	(void) argc;
	(void) argv;
	return (0);
}

static int	fill_str(char *file_name)
{
	char	str[100000];
	int		fd;

	ft_bzero(str, 99999);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	if (read(fd, str, 99999) == -1)
	{
		close(fd);
		return (-2);
	}
	write(1, str, 99999);
	dprintf(2, "\n\n\n\n");
	glb_parser(str + 20);
	return (0);
}
