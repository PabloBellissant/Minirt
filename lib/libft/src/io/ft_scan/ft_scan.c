/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:11:43 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/16 00:11:46 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "libft.h"

static int	skip_wildcard(char **line, char char_to_skip, int minimum, int num);
int			parse_type(va_list *args, char **line, int line_num, char *format);
static void	wrong_char_error(int line_num, char needed, char found);
static int	verif_char(char *format, char *line, int line_num);
static char	*skip_range(char *format);

int	ft_scan(int line_num, char *format, char *line, ...)
{
	va_list		args;

	va_start(args, line);
	while (*format/* || *line*/)
	{
		if (format[1] == '*' || format[1] == '+')
		{
			if (skip_wildcard(&line, *format, format[1] == '+', line_num) == -1)
				return (-1);
			++format;
		}
		else if (*format == '%')
		{
			++format;
			if (parse_type(&args, &line, line_num, format) == -1)
				return (-1);
			format = skip_range(format);
		}
		else if (verif_char(format, line, line_num) == -1)
			return (-1);
		else
			++line;
		++format;
	}
	return (0);
}

static char	*skip_range(char *format)
{
	if (format[1] == '[')
		format = ft_strchr(format, ']');
	return (format);
}

static int	verif_char(char *format, char *line, int line_num)
{
	if (*format != *line && !(*line == '\0' && *format == '\n'))
	{
		wrong_char_error(line_num, *format, *line);
		return (-1);
	}
	return (0);
}

static void	wrong_char_error(int line_num, char needed, char found)
{
	ft_putstr_fd("Error\nIncorrect character detected, found '", 2);
	write(2, &found, 1);
	ft_putstr_fd("' expecting '", 2);
	if (needed != '\n')
		write(2, &needed, 1);
	else
		ft_putstr_fd("new_line", 2);
	ft_putstr_fd("', line : '", 2);
	ft_putnbr_fd(line_num, 2);
	ft_putstr_fd("'\n", 2);
}

static int	skip_wildcard(char **line, char char_to_skip, int minimum, int num)
{
	int	i;

	i = 0;
	while ((*line)[i] == char_to_skip)
		++i;
	if (i < minimum)
	{
		ft_putstr_fd("Error\nNeed at least ", 2);
		ft_putnbr_fd(minimum, 2);
		if (char_to_skip != ' ')
		{
			ft_putstr_fd(" '", 2);
			write(2, &char_to_skip, 1);
			ft_putstr_fd("' ", 2);
		}
		else
			ft_putstr_fd(" space ", 2);
		ft_putstr_fd("between arguments, line '", 2);
		ft_putnbr_fd(num, 2);
		ft_putstr_fd("'\n", 2);
		return (-1);
	}
	(*line) += i;
	return (0);
}
