/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:22:58 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:03 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>

/**
 * @brief fills the first n bytes of the memory area pointed to by s 
 * with the constant byte c.
 * @param s memory area, c byte memory fill with, n number of bytes erase.
 * @return a pointer to the memory area s..
 * @author Bellissant Pablo
 */
void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	uint8_t			*ptr;

	i = 0;
	ptr = (uint8_t *)s;
	while (i < n)
	{
		*ptr = (uint8_t)c;
		++i;
		++ptr;
	}
	return (s);
}
