/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:01:54 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:00 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	*ft_lstclearandreturn(t_list **lst, void (*del)(void *));

/**
 * @brief Iterates the list ’lst’ and applies the function 
 * ’f’ on the content of each node. Creates a new 
 * list resulting of the successive applications of 
 * the function ’f’.
 * @param lst The address of a pointer to a node.
 * @param f The address of the function used to iterate on the list.
 * @param del The address of the function used to delete the content 
 * of a node if needed.
 * @return The new list, NULL if the allocation fails.
 * @author Bellissant Pablo
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*newnode;

	newlist = NULL;
	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	while (lst != NULL)
	{
		newnode = malloc(sizeof(t_list));
		if (!newnode)
			return (ft_lstclearandreturn(&newlist, del));
		newnode->content = f(lst->content);
		if (newnode->content == NULL)
		{
			free(newnode);
			return (ft_lstclearandreturn(&newlist, del));
		}
		newnode->next = NULL;
		ft_lstadd_back(&newlist, newnode);
		lst = lst->next;
	}
	return (newlist);
}

/**
 * This function is only used by ft_lstmap to clear the list 
 * and return in case of allocation fail
 */
static void	*ft_lstclearandreturn(t_list **lst, void (*del)(void *))
{
	ft_lstclear(lst, del);
	return (NULL);
}
