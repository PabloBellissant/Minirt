/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 04:36:48 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/13 04:36:49 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"
#include "struct.h"
#include "parsing.h"

static void	bad_ambient(int line_num);

int	ambient(char *line, int actual_line, t_scene *scene)
{
	line = ft_strtok(line, " ");
	line = ft_strtok(NULL, " ");
	if (line == NULL)
	{
		bad_ambient(actual_line);
		return (-1);
	}
	scene->ambient.ratio = parse_float(line, actual_line, 0, 1);
	if (scene->ambient.ratio == NAN)
		return (-1);
	line = ft_strtok(NULL, "");
	if (line == NULL)
	{
		bad_ambient(actual_line);
		return (-1);
	}
	if (parse_color(line, actual_line, &scene->ambient.color) == -1)
		return (-1);
	return (0);
}

static void	bad_ambient(int line_num)
{
	ft_putstr_fd("Error\nAmbient must be defined by 'A ratio R,G,B', ", 2);
	ft_putstr_fd("line : '", 2);
	ft_putnbr_fd(line_num, 2);
	ft_putstr_fd("'\n", 2);
}
