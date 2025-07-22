/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 06:22:09 by pabellis          #+#    #+#             */
/*   Updated: 2025/06/16 06:22:11 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_white_space(char c);

/**
 * @brief Convert a string to a long.
 * @param nptr The string to convert.
 * @return The resulted long.
 * @author Bellissant Pablo
 */
long	ft_atol(const char *nptr)
{
	long	result;
	int		negative_multiple;

	while (is_white_space(*nptr))
		++nptr;
	negative_multiple = 1;
	if (*nptr == '-')
		negative_multiple = -1;
	if (*nptr == '-' || *nptr == '+')
		++nptr;
	result = 0;
	while (ft_isdigit(*nptr))
	{
		result *= 10;
		result += (*nptr - '0');
		++nptr;
	}
	return (result * negative_multiple);
}

static bool	is_white_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}
