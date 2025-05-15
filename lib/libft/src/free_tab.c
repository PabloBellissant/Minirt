/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 19:01:52 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:39:48 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * @brief This function is used to free an array of strings.
 * @param tab A pointer to the array of strings.
 * @return 0 if the list not exist, 1 otherwise.
 * @author Bellissant Pablo
 */
int	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		++i;
	}
	free(tab);
	return (1);
}
