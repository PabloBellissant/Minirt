/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:52:41 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:06 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * @brief Search the first 'c' character in 's' string.
 * @param s The string to be look at.
 * @param c The character to find.
 * @return pointer to the first occurence of 
 * the character 'c' in the string 's', NULL if there is no c in the string 's'.
 * @author Bellissant Pablo
 */
char	*ft_strchr(const char *s, int c)
{
	c = (unsigned char) c;
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (NULL);
}
