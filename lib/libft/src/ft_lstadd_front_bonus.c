/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:23:12 by pabellis          #+#    #+#             */
/*   Updated: 2025/02/03 16:16:13 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Adds the node ’new’ at the beginning of the list.
 * @param lst The address of a pointer to the first link of a list.
 * @param new The address of a pointer to the node to be added to the list.
 * @author Bellissant Pablo
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}
