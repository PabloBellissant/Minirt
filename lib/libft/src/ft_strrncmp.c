/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 03:29:33 by pabellis          #+#    #+#             */
/*   Updated: 2025/04/09 03:29:36 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * @brief compares the last n bytes of the str s1 and s2.
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
int	ft_strrncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	s1_len;
	size_t	s2_len;

	if (n == 0)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (n > s1_len || n > s2_len)
		n = ft_min(s1_len, s2_len);
	i = 0;
	while (i < n - 1 && (s1[s1_len - i - 1] == s2[s2_len - i - 1]))
		++i;
	return (s1[s1_len - i - 1] - s2[s2_len - i - 1]);
}
