/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:16:49 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:10 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * @brief Put src at the end of dst, up to the size - 1 character. 
 * @param dst The destination.
 * @param src The source.
 * @param size the size max of the new dst.	
 * @return The initial length of dst + the length of src.
 * @warning The size of dst must be sufficient to accommodate dst and src.
 * @author Bellissant Pablo
 */
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;

	dst_len = ft_strlen(dst);
	if (size <= dst_len)
		return (ft_strlen(src) + size);
	i = 0;
	while ((i + dst_len) < (size - 1) && src[i])
	{
		dst[dst_len + i] = src[i];
		++i;
	}
	if (size > 0 && size > dst_len)
		dst[dst_len + i] = 0;
	return (dst_len + ft_strlen(src));
}
