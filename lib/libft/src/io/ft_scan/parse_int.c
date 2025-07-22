/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 06:16:39 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/16 06:17:41 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <errno.h>
#include "libft.h"

static bool	str_is_integer(char *line);
static void	print_val_not_range(int actual_line);
static void	print_exceed_size(int actual_line, int min, int max);

int	parse_int(char *line, int line_number, t_limits limits)
{
	int	result;

	errno = 0;
	if (!str_is_integer(line))
	{
		errno = EINVAL;
		print_val_not_range(line_number);
		return (0);
	}
	result = ft_atoi(line);
	if (result > limits.max || result < limits.min)
	{
		errno = EINVAL;
		print_exceed_size(line_number, limits.min, limits.max);
		return (0);
	}
	return (result);
}

static void	print_val_not_range(int actual_line)
{
	ft_putstr_fd("Error\nInvalid integer on line : '", 2);
	ft_putnbr_fd(actual_line, 2);
	ft_putstr_fd("'\n", 2);
}

static void	print_exceed_size(int actual_line, int min, int max)
{
	ft_putstr_fd("Error\nValue must be in range [", 2);
	ft_putnbr_fd(min, 2);
	ft_putstr_fd("-", 2);
	ft_putnbr_fd(max, 2);
	ft_putstr_fd("], line : '", 2);
	ft_putnbr_fd(actual_line, 2);
	ft_putstr_fd("'\n", 2);
}

static bool	str_is_integer(char *line)
{
	if (*line == '+' || *line == '-')
		++line;
	while (ft_isdigit(*line))
		++line;
	if (!*line || *line == ' ' || *line == ',' || *line == '\n')
		return (true);
	return (false);
}
