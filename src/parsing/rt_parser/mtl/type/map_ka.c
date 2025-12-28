/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_ka.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 23:48:44 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/11 06:50:29 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "parsing.h"

#define MAP_KA_FORMAT " *map_Ka  *%s *\n"

static void	scale_tex(t_texture *tex, t_vec3 *scale);

int	map_ka(const char *line, t_scene *scene)
{
	t_mat		*mat;
	char		*name;

	mat = get_last_vector_value(&scene->mat);
	if (ft_scan(0, MAP_KA_FORMAT, line, &name))
		return (-1);
	if (!parse_texture(scene, name))
		return (-1);
	scale_tex(get_last_vector_value(&scene->texture), &mat->ka);
	mat->ambient_id = (int) scene->texture.num_elements - 1;
	return (0);
}

static void	scale_tex(t_texture *tex, t_vec3 *scale)
{
	int	i;

	i = 0;
	while (i < tex->width * tex->height * tex->channels)
	{
		tex->pixels[i] *= scale->b;
		tex->pixels[i + 1] *= scale->g;
		tex->pixels[i + 2] *= scale->r;
		i += 3;
	}
}
