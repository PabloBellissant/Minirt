/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:21:53 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:01 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>

/**
 * @brief scans the initial n bytes of the memory area 
 * pointed to by s for the first instance of c.
 * @param s the memory area to scan.
 * @param c the character to find.
 * @param n the number of bytes max to search in.
 * @return pointer to the matching byte, NULL if the character 
 * does not occur in the given memory area.
 * @author Bellissant Pablo
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*((uint8_t *)s) == (uint8_t)c)
			return ((void *)s);
		i += 1;
		s += 1;
	}
	return (NULL);
}
