/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 05:24:20 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/14 05:24:21 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct.h"

static int	check_comma_num(char *str, int line_num);
static int	single_color_parse(uint8_t *return_val, char *line, int line_num);
static void	bad_format(int line_num);
static void	color_overflow(int line_num);

int	parse_color(char *str, int line_num, t_color *color)
{
	char	*save;

	if (check_comma_num(str, line_num) == -1)
		return (-1);
	str = ft_strtok_r(str, ",\n", &save);
	if (single_color_parse(&color->r, str, line_num) == -1)
		return (-1);
	str = ft_strtok_r(NULL, ",\n", &save);
	if (single_color_parse(&color->g, str, line_num) == -1)
		return (-1);
	str = ft_strtok_r(NULL, ",\n", &save);
	if (single_color_parse(&color->b, str, line_num) == -1)
		return (-1);
	str = ft_strtok_r(NULL, ",\n", &save);
	if (str)
	{
		if (single_color_parse(&color->a, str, line_num) == -1)
			return (-1);
	}
	return (0);
}

static int	single_color_parse(uint8_t *return_val, char *line, int line_num)
{
	int	temp;

	if (!ft_str_is_digit(line))
	{
		bad_format(line_num);
		return (-1);
	}
	temp = 0;
	if (*line == '+' || *line == '-')
		++temp;
	while (line[temp] == '0')
		++temp;
	if (ft_strlen(line) - temp > 3)
	{
		color_overflow(line_num);
		return (-1);
	}
	temp = ft_atoi(line);
	if (temp > 255 || temp < 0)
	{
		color_overflow(line_num);
		return (-1);
	}
	*return_val = temp;
	return (0);
}

static int	check_comma_num(char *str, int line_num)
{
	int		len;
	int		comma_count;

	len = 0;
	comma_count = 0;
	while (str[len] && str[len] != ' ')
	{
		if (str[len] == ',')
			++comma_count;
		++len;
	}
	if (comma_count != 2 && comma_count != 3)
	{
		bad_format(line_num);
		return (-1);
	}
	return (0);
}

static void	bad_format(int line_num)
{
	ft_putstr_fd("Error\nColor must be in format 'R,G,B' or 'R,G,B,A', ", 2);
	ft_putstr_fd("where R, G, B and A are integer in range [0:255], ", 2);
	ft_putstr_fd("line : '", 2);
	ft_putnbr_fd(line_num, 2);
	ft_putstr_fd("'\n", 2);
}

static void	color_overflow(int line_num)
{
	ft_putstr_fd("Error\nColor must be in range [0:255], ", 2);
	ft_putstr_fd("line : '", 2);
	ft_putnbr_fd(line_num, 2);
	ft_putstr_fd("'\n", 2);
}

