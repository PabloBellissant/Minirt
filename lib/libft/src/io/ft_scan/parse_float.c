/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:12:07 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/16 05:24:14 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "libft.h"

static bool	str_is_float(char *line);
static void	print_exceed_size(int actual_line, int min, int max);
static void	print_not_a_float(int actual_line);

float	parse_float(char *line, int line_number, t_limits limits)
{
	float	result;

	if (!str_is_float(line))
	{
		print_not_a_float(line_number);
		return (NAN);
	}
	if (*line == '+')
		++line;
	result = ft_atod(line);
	if (result > limits.max || result < limits.min)
	{
		print_exceed_size(line_number, limits.min, limits.max);
		return (NAN);
	}
	return (result);
}

static bool	str_is_float(char *line)
{
	int	i;

	i = 0;
	if (line[i] == '+' || line[i] == '-')
		++i;
	if (line[i] == '.' && !ft_isdigit(line[i + 1]))
		return (false);
	while (ft_isdigit(line[i]))
		++i;
	if (line[i] == '.')
		++i;
	while (ft_isdigit(line[i]))
		++i;
	if (*line && line[i] != '\0' && line[i] != ' ' && line[i] != ',')
		return (false);
	return (true);
}

static void	print_not_a_float(int actual_line)
{
	ft_putstr_fd("Error\nInvalid float format on line : '", 2);
	ft_putnbr_fd(actual_line, 2);
	ft_putstr_fd("'\n", 2);
}

static void	print_exceed_size(int actual_line, int min, int max)
{
	ft_putstr_fd("Error\nValue must be in range [", 2);
	ft_putnbr_fd(min, 2);
	ft_putstr_fd(".0-", 2);
	ft_putnbr_fd(max, 2);
	ft_putstr_fd(".0], line : '", 2);
	ft_putnbr_fd(actual_line, 2);
	ft_putstr_fd("'\n", 2);
}
