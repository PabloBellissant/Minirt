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

#include <stddef.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"

static void	parse_blend(char *file_name);

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (1);
	parse_blend(argv[1]);
	(void) argc;
	(void) argv;
	return (0);
}

static void	parse_blend(char *file_name)
{
	size_t	i;
	char	*str;
	int		fd;

	fd = open(file_name, O_RDONLY);
	str = get_next_line(fd);
	i = 0;
	while (i < 10)
	{
		str = get_next_line(fd);
		++i;
	}
}
