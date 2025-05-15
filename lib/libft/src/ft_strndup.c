/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:41:49 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:20 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * @brief Duplicate the entered string at most n bytes.
 * @param s The string to duplicate.
 * @param n The max number of byte to duplicate.
 * @return pointer to the new list.
 * @note The new string must be freed to avoid memory leaks.
 * @author Bellissant Pablo
 */
char	*ft_strndup(const char *s, size_t n)
{
	char			*newtab;
	size_t			i;
	size_t			slen;

	slen = ft_strlen(s);
	if (slen > n)
		slen = n;
	newtab = malloc(sizeof(char) * (slen + 1));
	if (!newtab)
		return (NULL);
	i = 0;
	while (i < slen)
	{
		newtab[i] = s[i];
		++i;
	}
	newtab[i] = 0;
	return (newtab);
}
