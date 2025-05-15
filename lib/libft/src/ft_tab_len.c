/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_len.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 00:56:04 by pabellis          #+#    #+#             */
/*   Updated: 2025/02/13 00:56:46 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/**
 * @brief Returns the length of a 2D array of void pointers.
 * @param tab A null-terminated array of void pointers.
 * @return The number of non-null elements in the array, or 0 if NULL.
 * @author Bellissant Pablo
 */
size_t	ft_tab_len(void **tab)
{
	size_t	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		++i;
	return (i);
}
