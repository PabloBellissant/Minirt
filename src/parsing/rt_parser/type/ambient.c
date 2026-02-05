/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 23:29:13 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/14 09:36:56 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "render.h"
#include "rt_xcerrcal.h"

#define AMBIENT_FORMAT " *A  *%f[1]  *%8[255] *, *%8[255] *, *%8[255] *\n"

int	ambient(const char *line, int line_num, t_scene *scene)
{
	t_rgb_int	color;
	float		ratio;

	if (ft_scan(line_num, AMBIENT_FORMAT, line, &ratio,
			&color.r, &color.g, &color.b))
	{
		return (error(pack_err(RT_ID, RT_E_AMBIENT), FL, LN, FC));
	}
	scene->ambient = get_real_ratio(color, ratio);
	return (0);
}
