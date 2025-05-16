/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:09:43 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:39:49 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_white_space(char c);

/**
 * @brief Convert a string to an integer.
 * @param nptr The string to convert.
 * @return The resulted integer.
 * @author Bellissant Pablo
 */
int	ft_atoi(const char *nptr)
{
	size_t	result;
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
	return ((int) result * negative_multiple);
}

static bool	is_white_space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}
