/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:07:42 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:07 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * @brief compares the first n bytes of the str s1 and s2.
 * @param s1 the first string to look at.
 * @param s2 the second string to look at.
 * @return return an integer less than, equal to, or greater than zero 
 * if s1 (or the first n bytes thereof) is found, respectively, 
 * to be less than, to match, or be greater than s2.
 * @author Bellissant Pablo
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] == s2[i]) && (s1[i] != 0))
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
