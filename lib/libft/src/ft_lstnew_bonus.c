/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:52:45 by pabellis          #+#    #+#             */
/*   Updated: 2025/01/23 03:40:01 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/**
 * @brief Allocates and returns a new node.
 * @param content The content to create the node with.
 * @return the new node.
 * @author Bellissant Pablo
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*link;

	link = malloc(sizeof(t_list));
	if (!link)
		return (NULL);
	link->content = content;
	link->next = NULL;
	return (link);
}
