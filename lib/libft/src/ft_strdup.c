/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:35:05 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:08 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * @brief Duplicate the entered string.
 * @param s The string to duplicate.
 * @return pointer to the new list.
 * @note The new string must be freed to avoid memory leaks.
 * @author Bellissant Pablo
 */
char	*ft_strdup(const char *s)
{
	char			*newtab;
	size_t			slen;

	slen = ft_strlen(s);
	newtab = malloc(sizeof(char) * (slen + 1));
	if (!newtab)
		return (NULL);
	ft_memcpy(newtab, s, slen + 1);
	return (newtab);
}
