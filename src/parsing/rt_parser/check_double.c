/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 03:26:31 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/05 04:07:46 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

static void	print_already_type(t_object_type type, int actual_line);

#define FORBIDEN_COUNT 3

int	check_float(t_object_type type, int actual_line)
{
	static t_object_type	forbidden_float[] = {AMBIENT, CAMERA};
	static int				elem_count[OBJ_ENUM_SIZE];
	unsigned long			i;

	i = 0;
	while (i < FORBIDEN_COUNT)
	{
		if (type == forbidden_float[i])
		{
			if (elem_count[type] == 1)
			{
				print_already_type(type, actual_line);
				return (-1);
			}
			elem_count[type] = 1;
			return (0);
		}
		++i;
	}
	return (0);
}

static void	print_already_type(t_object_type type, int actual_line)
{
	static char	*type_name[] = {"Undefined",
		"Ambient", "Camera", "Light", "Sphere", "Plane", "Cylinder"};

	ft_putstr_fd("Error\nMultiple assignation for type '", 2);
	ft_putstr_fd(type_name[type], 2);
	ft_putstr_fd("' is forbidden, line : '", 2);
	ft_putnbr_fd(actual_line, 2);
	ft_putstr_fd("'\n", 2);
}
