/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:11:43 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/07 09:32:13 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "libft.h"

static void	skip_wildcard(char **line, char char_to_skip);
int			parse_type(va_list *args, char **line, int line_num, char *format);
static void	wrong_char_error(int line_num, char needed, char found);
static int	verif_char(char *format, char **line, int line_num);
static char	*skip_range(char *format);

void	scan_optional_arg(va_list *args, char **format, char **line)
{
	va_list	copy;
	char	*line_backup;

	line_backup = *line;
	++*format;
	va_copy(copy, *args);
	while (**format && **format != ')')
	{
		if ((*format)[0] && (*format)[1] == '*')
		{
			skip_wildcard(line, **format);
			++*format;
		}
		else if (**format == '%')
		{
			++*format;
			if (parse_type(&copy, line, -1, *format) == -1)
			{
				*line = line_backup;
				break ;
			}
			*format = skip_range(*format);
		}
		else if (verif_char(*format, line, -1) == -1)
		{
			*line = line_backup;
			break ;
		}
		++*format;
	}
	*format = ft_strchr(*format, ')') + 1;
}

int	ft_scan(int line_num, char *format, char *line, ...)
{
	va_list		args;

	va_start(args, line);
	while (*format)
	{
		if (format[0] == '(')
			scan_optional_arg(&args, &format, &line);
		if (format[0] && format[1] == '*')
		{
			skip_wildcard(&line, *format);
			++format;
		}
		else if (*format == '%')
		{
			++format;
			if (parse_type(&args, &line, line_num, format) == -1)
				return (-1);
			format = skip_range(format);
		}
		else if (verif_char(format, &line, line_num) == -1)
			return (-1);
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

static int	verif_char(char *format, char **line, int line_num)
{
	if (*format != **line && !(**line == '\0' && *format == '\n')
		&& !(ft_isspace(*format) && ft_isspace(**line)))
	{
		if (line_num == -1)
			return (-1);
		wrong_char_error(line_num, *format, **line);
		return (-1);
	}
	++*line;
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

static void	skip_wildcard(char **line, const char char_to_skip)
{
	while (**line == char_to_skip
		|| (ft_isspace(char_to_skip) && ft_isspace(**line)))
		++*line;
}
