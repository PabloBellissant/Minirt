/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:52:28 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/20 17:29:48 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"

#define SKY_FORMAT " *sky  *%s *\n"

int	sky(const char *line, int line_num, t_scene *scene)
{
	char		*texture_path;
	t_texture	*texture;

	if (ft_scan(line_num, SKY_FORMAT, line, &texture_path))
	{
		free(texture_path);
		return (error(pack_err(RT_ID, RT_E_SKY), FL, LN, FC));
	}
	texture = parse_texture(scene, texture_path);
	if (!texture)
	{
		register_complex_err_msg(RT_E_MSG_NO_TEX, texture_path);
		free(texture_path);
		return (error(pack_err(RT_ID, RT_E_NO_TEX), FL, LN, FC));
	}
	texture->name = texture_path;
	scene->skybox_tex = scene->texture.num_elements - 1;
	return (0);
}
