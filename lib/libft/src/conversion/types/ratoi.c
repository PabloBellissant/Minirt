/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ratoi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:53:56 by jaubry--          #+#    #+#             */
/*   Updated: 2025/04/17 20:50:31 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdbool.h>

static int	overflowing(char *str, int neg);

int	ratoi(const char *str)
{
	size_t		i;
	long long	num;
	int			neg;

	neg = 1;
	i = 0;
	num = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		neg = -1;
	if ((str[i] == '+') || (str[i] == '-'))
		i++;
	if (ft_isdigit(str[i]) && (overflowing((char *)str + i, neg) != 0))
		return (overflowing((char *)str + i, neg));
	while (ft_isdigit(str[i]))
	{
		num *= 10;
		num += str[i] - '0';
		i++;
	}
	return (neg * num);
}

static int	overflowing(char *str, int neg)
{
	size_t	len;

	len = 0;
	while (str[len] && ft_isdigit(str[len]))
		len++;
	if (neg == 1)
	{
		if ((len > 10) || ((len == 10)
				&& (ft_strncmp("2147483647", str, 10) < 0)))
			return (-1);
	}
	else if (neg == -1)
	{
		if ((len > 10) || ((len == 10)
				&& (ft_strncmp("2147483648", str, 10) < 0)))
			return (1);
	}
	return (0);
}

bool	check_flow(char *str, int ret)
{
	int		neg;
	size_t	i;

	i = 0;
	neg = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		neg = -1;
	if ((str[i] == '+') || (str[i] == '-'))
		i++;
	if (ft_isdigit(str[i]))
	{
		if ((ret == 1) && (neg == -1))
			return (1);
		else if ((ret == -1) && (neg == 1))
			return (1);
	}
	return (0);
}
