/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:18:24 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:02 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>

/**
 * @brief copies n bytes from memory area src to memory area dest.
 * @param dest the destination memory area.
 * @param src the source memory area.
 * @param n the number of bytes max to copy.
 * @return pointer to the matching byte, NULL if the character 
 * does not occur in the given memory area.
 * @attention The memory area must not overlap.
 * @see ft_memmove if the memory area may overlap.
 * @author Bellissant Pablo
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	uint8_t	*ptr;

	i = 0;
	ptr = (uint8_t *) dest;
	while (i < n)
	{
		ptr[i] = (*(uint8_t *) src);
		++i;
		++src;
	}
	return (dest);
}
