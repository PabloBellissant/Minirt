/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 04:36:48 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/31 20:40:15 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct.h"
#include "parsing.h"

#define AMBIENT_FORMAT " *A +%f[1] +%8[255] *, *%8[255] *, *%8[255] *\n"

int	ambient(char *line, int line_num, t_scene *scene)
{
	t_ambient	*ambient;
	t_color		*color;
	int			ret;

	ret = 0;
	ambient = &scene->ambient;
	color = &ambient->color;
	ret = ft_scan(line_num, AMBIENT_FORMAT, line, &ambient->ratio,
			&color->r, &color->g, &color->b);
	get_real_ratio(color, ambient->ratio, &ambient->col);
	return (ret);
}
