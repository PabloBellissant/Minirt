/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:44:38 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:13 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * @brief copy src to dst. 
 * @param dst The destination.
 * @param src The source.
 * @param size the size max.
 * @return The length of src.
 * @warning The size of dst must be sufficient to accommodate src.
 * @author Bellissant Pablo
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (src[i] != 0 && i + 1 < size)
	{
		dst[i] = src[i];
		i += 1;
	}
	if (size > 0)
		dst[i] = 0;
	while (src[i])
		i += 1;
	return (i);
}
