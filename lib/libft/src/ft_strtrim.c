/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:34:29 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:21 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_isincharset(char *charset, char c);

/**
 * @brief Allocates and returns a copy of ’s1’ with the characters specified 
 * in ’set’ removed from the beginning and the end of the string.
 * @param s1 The string to be trimmed.
 * @param set The reference set of characters to trim.
 * @return The trimmed string. NULL if the allocation fails.
 * @note The returned string must be freed to avoid memory leaks.
 * @author Bellissant Pablo
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	s1len;
	char	*newstr;

	while (ft_isincharset((char *)set, s1[0]))
		s1 += 1;
	s1len = ft_strlen(s1);
	if (s1len > 0)
		while (ft_isincharset((char *)set, s1[s1len - 1]))
			s1len -= 1;
	newstr = malloc(sizeof(char) * s1len + 1);
	if (!newstr)
		return (0);
	i = 0;
	while (i < s1len)
	{
		newstr[i] = s1[i];
		i += 1;
	}
	newstr[i] = 0;
	return (newstr);
}

/**
 * @brief find if character 'c' is in charset.
 * @param charset The string charset.
 * @param c the character to find in charset.
 * @return 1 if c is in charset, 0 otherwise.
 * @warning the charset must not be NULL.
 * @author Bellissant Pablo
 */
static int	ft_isincharset(char *charset, char c)
{
	while (charset[0])
	{
		if (charset[0] == c)
			return (1);
		charset++;
	}
	return (0);
}
