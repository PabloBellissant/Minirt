/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:42:13 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:21 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * @brief Allocates and returns a substring from the string ’s’. 
 * The substring begins at index ’start’ and is of maximum size ’len’.
 * @param s The string from which to create the substring.
 * @param start The start index of the substring in the string ’s’.
 * @param len The maximum length of the substring.
 * @return The substring. NULL if the allocation fails.
 * @note The returned string must be freed to avoid memory leaks.
 * @author Bellissant Pablo
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*newstr;
	size_t		i;
	size_t		slen;

	slen = 0;
	if (start < ft_strlen(s))
		slen = ft_strlen(s) - start;
	if (slen > len)
		slen = len;
	newstr = ft_calloc(slen + 1, sizeof(char));
	if (!newstr)
		return (NULL);
	i = 0;
	while (i < slen && s[i + start])
	{
		newstr[i] = s[i + start];
		i += 1;
	}
	return (newstr);
}
