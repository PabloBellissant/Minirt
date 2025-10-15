/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 23:37:25 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/14 06:54:39 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "calc.h"
#include "rt_xcerrcal.h"

#define TEXTURE_FORMAT " *tex  *%s  *%s *\n"

int	tex(const char *line, int line_num, t_scene *scene)
{
	t_texture	*tex;
	char		*name;
	char		*path;

	if (ft_scan(line_num, TEXTURE_FORMAT, line, &name, &path))
	{
		return (error(pack_err(RT_ID, RT_E_TEX), FL, LN, FC));
	}
	tex = create_texture(scene, path);
	if (!tex)
	{
		register_complex_err_msg(RT_E_MSG_NO_TEX, name);
		return (error(pack_err(RT_ID, RT_E_NO_TEX), FL, LN, FC));
	}
	tex->name = name;
	return (0);
}
