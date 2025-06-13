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

#include "libft.h"
#include "struct.h"

static void	print_bad_ratio_length(int actual_line);
static void	print_bad_ratio_size(int actual_line);

int	ambient(char *line, int actual_line, t_scene *scene)
{
	int	len;

	while (*line == ' ' || *line == '\t')
		++line;
	++line;
	if (line[0] == '\0')
		return (-1);
	while (*line == ' ' || *line == '\t')
		++line;
	if (line[0] == '\0')
		return (-1);
	len = 0;
	while (line[len] && line[len] != ' ' && line[len] != '\t')
		++len;
	if (len > 8)
	{
		print_bad_ratio_length(actual_line);
		return (-1);
	}
	scene->ambient.ratio = (float) ft_atod(line);
	if (scene->ambient.ratio > 1 || scene->ambient.ratio < 0)
		print_bad_ratio_size(actual_line);
	else
		return (0);
	return (-1);
}

static void	print_bad_ratio_length(int actual_line)
{
	ft_putstr_fd("Error\nRatio value cannot exceed 10 length, line : '", 2);
	ft_putnbr_fd(actual_line, 2);
	ft_putstr_fd("'\n", 2);
}

static void	print_bad_ratio_size(int actual_line)
{
	ft_putstr_fd("Error\nRatio value must be in range [0.0:1.0], line : '", 2);
	ft_putnbr_fd(actual_line, 2);
	ft_putstr_fd("'\n", 2);
}
