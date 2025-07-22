/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:19:18 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:20 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * @brief find the string 'little' in the string 'big'
 * @param big The big string.
 * @param little The string to find in big.
 * @param len the maximum len.
 * @return If little is an empty string, big is returned; if little occurs 
 * nowhere in big, NULL is returned; otherwise a pointer to the first character 
 * of the first occurrence of little is returned.
 * @author Bellissant Pablo
 */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	y;

	if (little[0] == 0)
		return ((char *) big);
	i = 0;
	while (big[i])
	{
		y = 0;
		while (big[i + y] == little[y] && (y + i) < len && little[y])
			y += 1;
		if (little[y] == 0)
			return ((char *)(big + i));
		i += 1;
	}
	return (NULL);
}
