/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 23:10:16 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/11 06:50:11 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx_wrapper.h"
#include "render.h"
#include "parsing.h"

#define MAP_PM_FORMAT " *map_Pm  *%s *\n"

static void	scale_pm(t_texture *tex, t_texture *pm);

int	map_pm(const char *line, t_scene *scene)
{
	t_mat		*mat;
	char		*name;

	mat = get_last_vector_value(&scene->mat);
	if (ft_scan(0, MAP_PM_FORMAT, line, &name))
		return (-1);
	if (!parse_texture(scene, name))
		return (-1);
	scale_pm(get_last_vector_value(&scene->texture), \
	   get_vector_value(&scene->texture, mat->metalness_id));
	mat->metalness_id = (int) scene->texture.num_elements - 1;
	return (0);
}

static void	scale_pm(t_texture *tex, t_texture *pm)
{
	int	i;
	int	temp;

	i = 0;
	while (i < tex->width * tex->height * tex->channels)
	{
		temp = (int) tex->pixels[i];
		temp *= pm->pixels[0] / 255;
		if (temp > 255)
			temp = 255;
		tex->pixels[i] = temp;
		++i;
	}
}

