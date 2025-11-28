/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mtllib.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 18:35:18 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/21 18:35:19 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define MTLLIB_FORMAT " *mtllib  *%s *\n"

int	parse_mtllib(const char *line, t_scene *scene)
{
	char	*str;
	int		fd;

	if (ft_scan(0, MTLLIB_FORMAT, line, &str))
		return (-1);
	fd = open(str, O_RDONLY);
	free(str);
	if (fd == -1)
		return (-1);
	return (parse_mtl_file(fd, scene));
}
