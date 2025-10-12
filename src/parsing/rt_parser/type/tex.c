/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 23:37:25 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/09 23:37:27 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "calc.h"

#define TEXTURE_FORMAT " *tex  *%s  *%s *\n"

int	tex(const char *line, int line_num, t_scene *scene)
{
	t_texture	*tex;
	char		*name;
	char		*path;

	if (ft_scan(line_num, TEXTURE_FORMAT, line, &name, &path))
		return (-1);
	tex = create_texture(scene, path);
	if (!tex)
		return (-1);
	tex->name = name;
	return (0);
}
