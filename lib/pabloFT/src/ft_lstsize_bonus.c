/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:53:45 by pabellis          #+#    #+#             */
/*   Updated: 2024/12/15 07:50:51 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * @brief Counts the number of nodes in a list.
 * @param lst the beginning of the list.
 * @return the length of the list
 * @author Bellissant Pablo
 */
int	ft_lstsize(t_list *lst)
{
	size_t	i;

	i = 1;
	if (lst == NULL)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
		i += 1;
	}
	return (i);
}
