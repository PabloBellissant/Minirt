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

#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include "libft.h"

static char	*skip_wildcard(char *line, char char_to_skip, int minimum, int num);
static int	parse_type(char type, va_list *args, char **line, int line_num, char *format);
static void	wrong_char_error(int line_num, char needed, char found);

int	ft_scan(int line_num, char *format, char *line, ...)
{
	va_list		args;

	va_start(args, line);
	while (*format)
	{
		if (format[1] == '*' || format[1] == '+')
		{
			line = skip_wildcard(line, *format, format[1] == '+', line_num);
			++format;
		}
		else if (*format == '%')
		{
			++format;
			if (parse_type(*format, &args, &line, line_num, format) == -1)
				return (-1);
			if (format[1] == '[')
				format = ft_strchr(format, ']');
		}
		else if (*format != *line)
		{
			dprintf(2, "error here %s\n", line);
			wrong_char_error(line_num, *format, *line);
			return (-1);
		}
		else
			++line;
		++format;
	}
	return (0);
}

static void	wrong_char_error(int line_num, char needed, char found)
{
	ft_putstr_fd("Error\nIncorrect character detected, found '", 2);
	write(2, &found, 1);
	ft_putstr_fd("' expecting '", 2);
	write(2, &needed, 1);
	ft_putstr_fd("', line :", 2);
	ft_putnbr_fd(line_num, 2);
	ft_putstr_fd("'\n", 2);
}

static char	*get_end_token(char *line, char type)
{
	if (*line == '+' || *line == '-')
		++line;
	if (type == 'd' || type == '8')
	{
		while (ft_isdigit(*line))
			++line;
	}
	else if (type == 'f')
	{
		while (ft_isdigit(*line))
			++line;
		if (*line == '.')
			++line;
		while (ft_isdigit(*line))
			++line;
	}
	return (line);
}

t_limits	get_limits(char type, char *format)
{
	int	temp;

	++format;
	if (*format != '[')
	{
		if (type == 'd')
			return ((t_limits) {INT_MIN, INT_MAX});
		if (type == '8')
			return ((t_limits) {0, 255});
		return ((t_limits) {-2147483648, 2147483647});
	}
	++format;
	if (!ft_strchr(format, ',') || ft_strchr(format, ',') > ft_strchr(format, ']'))
		return ((t_limits) {0, ft_atoi(format)});
	temp = ft_atoi(format);
	format = ft_strchr(format, ',') + 1;
	return ((t_limits) {temp, ft_atoi(format)});
}

static int	parse_type(char type, va_list *args, char **line, int line_num, char *format)
{
	float	*float_result;
	int		*int_result;
	uint8_t	*uint8_result;

	if (type == 'f')
	{
		float_result = va_arg(*args, float *);
		*float_result = parse_float(*line, line_num, get_limits(type, format));
		if (*float_result == NAN)
			return (-1);
	}
	else if (type == 'd')
	{
		int_result = va_arg(*args, int *);
		*int_result = parse_int(*line, line_num, get_limits(type, format));
	}
	else if (type == '8')
	{
		uint8_result = va_arg(*args, uint8_t *);
		*uint8_result = parse_int(*line, line_num, get_limits(type, format));
	}
	if (errno == EINVAL)
		return (-1);
	*line = get_end_token(*line, type);
	return (0);
}

static char	*skip_wildcard(char *line, char char_to_skip, int minimum, int num)
{
	int	i;

	i = 0;
	if (line[i] == char_to_skip)
	{
		while (line[i] == char_to_skip)
			++i;
	}
	if (i < minimum)
	{
		ft_putstr_fd("Error\nNeed at least ", 2);
		ft_putnbr_fd(minimum, 2);
		ft_putstr_fd("'", 2);
		write(2, &char_to_skip, 1);
		ft_putstr_fd("' between args at line '", 2);
		ft_putnbr_fd(num, 2);
		ft_putstr_fd("'\n", 2);
		return (NULL);
	}
	return (line + i);
}
