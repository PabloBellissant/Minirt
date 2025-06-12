/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 03:26:31 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/12 03:26:32 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "parsing.h"

static void	print_already_camera(int actual_line);
static void	print_already_ambient(int actual_line);

int	check_double(t_object_type type, int actual_line)
{
	static bool		have_camera = false;
	static bool		have_ambient = false;

	if (type == CAMERA && have_camera)
	{
		print_already_camera(actual_line);
		return (-1);
	}
	if (type == AMBIENT && have_ambient)
	{
		print_already_ambient(actual_line);
		return (-1);
	}
	if (type == CAMERA)
		have_camera = true;
	else if (type == AMBIENT)
		have_ambient = true;
	return (0);
}

static void	print_already_camera(int actual_line)
{
	ft_putstr_fd("Error\nCamera double initialization, line : '", 2);
	ft_putnbr_fd(actual_line, 2);
	ft_putstr_fd("'\n", 2);
}

static void	print_already_ambient(int actual_line)
{
	ft_putstr_fd("Error\nAmbient lightning double initialization, line : '", 2);
	ft_putnbr_fd(actual_line, 2);
	ft_putstr_fd("'\n", 2);
}
