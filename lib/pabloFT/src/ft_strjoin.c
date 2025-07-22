/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:23:57 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:10 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * @brief Concatenate s1 and s2
 * @param s1 The prefix string.
 * @param s2 The suffic string.
 * @return The new string, NULL if the allocaton fails.
 * @note the returned string must be freed to avoid memory leaks.
 * @warning s1 and s2 must not be NULL.
 * @author Bellissant Pablo
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*newstr;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	newstr = malloc(s1len + s2len + 1);
	if (!newstr)
		return (NULL);
	ft_memcpy(newstr, s1, s1len);
	ft_memcpy(newstr + s1len, s2, s2len + 1);
	return (newstr);
}
