/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getintlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 02:47:16 by pabellis          #+#    #+#             */
/*   Updated: 2025/02/13 02:47:16 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/**
 * @brief Get the number of digits needed to write the entered integer.
 * @param n the integer to get len from.
 * @return The len of the entered integer.
 * @example 4242 -> 4, 2147483647 -> 10, 5 -> 1
 * @author Bellissant Pablo
 */
size_t	ft_getintlen(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		++i;
	while (n >= 10 || n <= -10)
	{
		n /= 10;
		++i;
	}
	return (i);
}
