/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:17:37 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:39:50 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

/**
 * @brief Allocate NMEMB elements of SIZE bytes each, all initialized to 0.
 * @param nmemb number of element
 * @param size the size of element
 * @return a pointer to the allocate memory.
 * @author Bellissant Pablo
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tab;

	if (!nmemb || !size)
		return (malloc(0));
	if (size > SIZE_MAX / nmemb)
		return (NULL);
	tab = malloc(nmemb * size);
	if (!tab)
		return (NULL);
	ft_bzero(tab, nmemb * size);
	return (tab);
}
