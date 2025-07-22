/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:07:42 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:19 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * @brief compares the first n bytes of the str s1 and s2.
 * @param s1 the first string to look at.
 * @param s2 the second string to look at.
 * @param n The size max to compare.
 * @return returns an integer less than, equal to, or greater than zero if 
 * the first n bytes of s1 is found, respectively, to be less than,
 * to match, or be greater than the first n bytes of s2.
 * For a nonzero return value, the sign is determined by the sign of the 
 * difference between the first pair of bytes that differ in s1 and s2.
 * If n is zero, the return value is zero.
 * @author Bellissant Pablo
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while ((s1[i] == s2[i]) && (s1[i] != 0) && (n > i + 1))
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
