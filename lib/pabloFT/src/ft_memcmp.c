/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:42:24 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:02 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>

/**
 * @brief compares the first n bytes of the memory areas s1 and s2.
 * @param s1 the first memory area to look at.
 * @param s2 the second memory area to look at.
 * @return returns an integer less than, equal to, or greater than zero if 
 * the first n bytes of s1 is found, respectively, to be less than,
 * to match, or be greater than the first n bytes of s2.
 * For a nonzero return value, the sign is determined by the sign of the 
 * difference between the first pair of bytes that differ in s1 and s2.
 * If n is zero, the return value is zero.

 * @author Bellissant Pablo
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	uint8_t	*str1;
	uint8_t	*str2;

	str1 = (uint8_t *)s1;
	str2 = (uint8_t *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (str1[i] == str2[i] && i < n - 1)
		i += 1;
	return (str1[i] - str2[i]);
}
