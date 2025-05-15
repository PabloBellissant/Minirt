/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 11:37:21 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:39:59 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * @brief Takes as a parameter a node and frees the memory of 
 * the node’s content using the function ’del’ given 
 * as a parameter and free the node.
 * @param lst The node to free.
 * @param del The address of the function used to delete 
 * the content.
 * @author Bellissant Pablo
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst != NULL && del != NULL)
	{
		del(lst->content);
		free(lst);
	}
}
