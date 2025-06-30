/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 04:44:01 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/18 04:44:06 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include <errno.h>
#include <limits.h>
#include "libft.h"

float			parse_float(char *line, int line_number, t_limits limits);
int				parse_int(char *line, int line_number, t_limits limits);
static t_limits	limits(char type, char *format);
static char		*get_end_token(char *line);

int	parse_type(va_list *args, char **line, int line_num, char *format)
{
	t_result	result;

	if (*format == 'f')
	{
		result.float_t = va_arg(*args, float *);
		*result.float_t = parse_float(*line, line_num, limits(*format, format));
		if (*result.float_t == NAN)
			return (-1);
	}
	else if (*format == 'd')
	{
		result.int_t = va_arg(*args, int *);
		*result.int_t = parse_int(*line, line_num, limits(*format, format));
	}
	else if (*format == '8')
	{
		result.uint8_t = va_arg(*args, uint8_t *);
		*result.uint8_t = parse_int(*line, line_num, limits(*format, format));
	}
	if (errno == EINVAL)
		return (-1);
	*line = get_end_token(*line);
	return (0);
}

static t_limits	limits(char type, char *format)
{
	int	temp;

	++format;
	if (*format != '[')
	{
		if (type == 'd')
			return ((t_limits){INT_MIN, INT_MAX});
		if (type == '8')
			return ((t_limits){0, 255});
		return ((t_limits){-2147483648, 2147483647});
	}
	++format;
	if (!ft_strchr(format, ',')
		|| ft_strchr(format, ',') > ft_strchr(format, ']'))
	{
		return ((t_limits){0, ft_atoi(format)});
	}
	temp = ft_atoi(format);
	format = ft_strchr(format, ',') + 1;
	return ((t_limits){temp, ft_atoi(format)});
}

static char	*get_end_token(char *line)
{
	while (*line && *line != ' ' && *line != '\n' && *line != ',')
		++line;
	return (line);
}
