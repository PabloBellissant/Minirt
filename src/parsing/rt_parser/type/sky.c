/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:52:28 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/09 19:52:31 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "calc.h"

#define SKY_FORMAT " *sky  *%s *\n"

int	sky(const char *line, int line_num, t_scene *scene)
{
	char	*texture_name;

	(void) scene;
	if (ft_scan(line_num, SKY_FORMAT, line, &texture_name))
		return (-1);
	scene->skybox = get_texture(scene, texture_name);
	if (!scene->skybox)
	{
		ft_dprintf(2, "Error\nCannot find texture '%s', line : '%d'\n", texture_name, line_num);
		return (-1);
	}
	return (0);
}
