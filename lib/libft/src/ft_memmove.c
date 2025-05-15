/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:24:16 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:03 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>

/**
 * @brief copies n bytes from memory area src to memory area dest.
 * @param dest the destination memory area.
 * @param src the source memory area.
 * @param n the number of bytes max to copy.
 * @note The memory area can overlap.
 * @author Bellissant Pablo
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	uint8_t			*ptr;

	i = 0;
	ptr = (uint8_t *) dest;
	if (src >= dest)
		while (i < n)
			ptr[i++] = (*(uint8_t *) src++);
	else
		while (n-- > 0)
			ptr[n] = (*(uint8_t *)(src + n));
	return (dest);
}
