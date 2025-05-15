/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 12:34:23 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:39:59 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Iterates the list ’lst’ and applies the function 
 * ’f’ on the content of each node.
 * @param lst The address of a pointer to a node.
 * @param f The address of the function used to iterate on the list.
 * @author Bellissant Pablo
 */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (lst != 0 || f != 0)
	{
		while (lst)
		{
			f(lst->content);
			lst = lst->next;
		}
	}
}
