/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_kd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 05:14:38 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/21 05:14:50 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "parsing.h"

#define MAP_KD_FORMAT " *map_Kd  *%s *\n"

static void	scale_tex(t_texture *tex, t_vec3 *scale);

int	map_kd(const char *line, t_scene *scene)
{
	t_mat		*mat;
	char		*name;

	mat = get_last_vector_value(&scene->mat);
	if (ft_scan(0, MAP_KD_FORMAT, line, &name))
		return (-1);
	if (!parse_texture(scene, name))
		return (-1);
	scale_tex(get_last_vector_value(&scene->texture), &mat->kd);
	mat->kd_id = (int) scene->texture.num_elements - 1;
	if (mat->kd_id == -1)
		return (-1);
	return (0);
}

static void	scale_tex(t_texture *tex, t_vec3 *scale)
{
	int	i;

	i = 0;
	while (i < tex->width * tex->height * (tex->tex_bpp / 8))
	{
		tex->pixels[i] *= scale->data[2];
		tex->pixels[i + 1] *= scale->data[1];
		tex->pixels[i + 2] *= scale->data[0];
		i += 3;
	}
}
