/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 08:14:46 by jaubry--          #+#    #+#             */
/*   Updated: 2025/04/17 20:50:20 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdbool.h>

static bool	will_overflow(long long a, int b);

int	ft_atoi(const char *str)
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
	while (ft_isdigit(str[i]))
	{
		if (will_overflow(num, str[i] - '0'))
			return (0);
		num *= 10;
		num += str[i] - '0';
		i++;
	}
	return (neg * num);
}

/*
	Function that returns 1 if multiplying a by 10 and adding b will cause
	an overflow otherwise 0
	a can only be positive as well as b
*/

static bool	will_overflow(long long a, int b)
{
	if (a)
	{
		if (10 > (LLONG_MAX / a))
			return (true);
	}
	a *= 10;
	if (b > (LLONG_MAX - a))
		return (true);
	return (false);
}
