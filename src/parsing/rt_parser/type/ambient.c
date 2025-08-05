/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 04:36:48 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 05:06:26 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "render.h"
#include "vec3.h"

#define AMBIENT_FORMAT " *A +%f[1] +%8[255] *, *%8[255] *, *%8[255] *\n"

int	ambient(char *line, int line_num, t_scene *scene)
{
	t_ambient	*ambient;
	t_color		color;

	ambient = &scene->ambient;
	if (ft_scan(line_num, AMBIENT_FORMAT, line, &ambient->ratio,
			&color.r, &color.g, &color.b))
		return (-1);
	get_real_ratio(&color, ambient->ratio, &ambient->rgb);
	return (0);
}
