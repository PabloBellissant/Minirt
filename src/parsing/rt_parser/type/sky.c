/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 19:52:28 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/14 06:42:35 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "calc.h"
#include "rt_xcerrcal.h"

#define SKY_FORMAT " *sky  *%s *\n"

int	sky(const char *line, int line_num, t_scene *scene)
{
	char	*texture_name;

	(void) scene;
	if (ft_scan(line_num, SKY_FORMAT, line, &texture_name))
	{
		free(texture_name);
		return (error(pack_err(RT_ID, RT_E_SKY), FL, LN, FC));
	}
	scene->skybox_tex = get_texture(scene, texture_name);
	if (scene->skybox_tex == -1)
	{
		register_complex_err_msg(RT_E_MSG_NO_TEX, texture_name);
		free(texture_name);
		return (error(pack_err(RT_ID, RT_E_NO_TEX), FL, LN, FC));
	}
	free(texture_name);
	return (0);
}
