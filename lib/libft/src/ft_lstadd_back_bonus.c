/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 00:20:08 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:39:58 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Adds the node ’new’ at the end of the list.
 * @param lst The address of a pointer to the first link of a list.
 * @param new The address of a pointer to the node to be added to the list.
 * @author Bellissant Pablo
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*actual;

	if (lst == NULL)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	actual = ft_lstlast(*lst);
	actual->next = new;
}
