/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 22:56:29 by pabellis          #+#    #+#             */
/*   Updated: 2025/11/23 22:56:32 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <fcntl.h>
#include "render.h"

#define MTL_FORMAT " *mtl  *%s *\n"

int	mtl(const char *line, int line_num, t_scene *scene)
{
	char	*mtl_path;
	int		fd;

	if (ft_scan(line_num, MTL_FORMAT, line, &mtl_path) == -1)
		return (-1);
	fd = open(mtl_path, O_RDONLY);
	if (fd == -1)
		return (-1);
	if (scene->mtl_list.num_elements == 0)
		vector_init(&scene->mtl_list, sizeof(char *));
	if (vector_add(&scene->mtl_list, &mtl_path, 1) == -1)
	{
		close(fd);
		return (-1);
	}
	return (parse_mtl_file(fd, scene));
}
