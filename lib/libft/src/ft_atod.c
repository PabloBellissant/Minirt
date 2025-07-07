/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 01:36:39 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/17 01:36:42 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atod(char *str)
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
