/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 06:07:52 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/11 06:07:54 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <errno.h>
#include "libft.h"
#include "struct.h"

int	rt_parser(int fd, t_scene *scene)
{
	char	*line;
	int		return_val;

	errno = 0;
	return_val = 0;
	line = get_next_line(fd);
	while (line)
	{
		// if (set_on_scene(scene, line) != 0)
		// 	return_val = -1;
		line = get_next_line(fd);
	}
	if (!line && errno != 0)
	{
		return_val = -1;
		perror("Minirt");
	}
	if (return_val != 0)
		// clear_scene(scene);
	return (return_val);
}
