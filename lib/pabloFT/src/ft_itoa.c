/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:45:38 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:39:57 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * @brief Convert integer to a string
 * @param n the integer to transform in string
 * @return The string containing the int in ascii, NULL if the allocation fail.
 * @note The returned string must be freed.
 * @author Bellissant Pablo
 */
char	*ft_itoa(int n)
{
	int		i;
	char	*output;
	long	long_n;
	int		neg;

	neg = 0;
	long_n = (long) n;
	if (n < 0)
		neg = 1;
	i = 1 + ft_getintlen(n);
	output = malloc(sizeof(char) * (i + 1));
	if (!output)
		return (NULL);
	output[i] = 0;
	if (long_n < 0)
		output[0] = '-';
	while ((--i >= 0 && neg == 0) || (i >= 1 && neg == 1))
	{
		output[i] = ft_abs(long_n % 10) + '0';
		long_n /= 10;
	}
	return (output);
}
