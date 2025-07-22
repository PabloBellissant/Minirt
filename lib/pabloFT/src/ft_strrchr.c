/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:57:07 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:20 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Search the last 'c' character in 's' string.
 * @param s The string to be look at.
 * @param c The character to find.
 * @return pointer to the last occurence of 
 * the character 'c' in the string 's'.
 * @author Bellissant Pablo
 */
char	*ft_strrchr(const char *s, int c)
{
	long	i;
	char	*temp;

	i = (long) ft_strlen(s);
	c = (unsigned char) c;
	while (i >= 0)
	{
		if (s[i] == c)
		{
			temp = (char *)s;
			return (temp + i);
		}
		--i;
	}
	return (NULL);
}
