/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 01:36:39 by pabellis          #+#    #+#             */
/*   Updated: 2025/07/23 00:42:24 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atod(const char *str)
{
	float		result;
	long long	depth;
	int			sign;

	result = 0.0;
	depth = 1;
	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		++str;
	}
	while (ft_isdigit(*str) || *str == '.')
	{
		if (depth == 1 && *str != '.')
			result *= 10;
		if (ft_isdigit(*str))
			result += (float)((*str) - '0') / depth;
		if (*str == '.')
			depth = 10;
		else if (depth > 1)
			depth *= 10;
		++str;
	}
	return (result * sign);
}
