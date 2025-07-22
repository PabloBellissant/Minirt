/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:32:05 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/03/16 17:03:53 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_front(t_dlist **lst, t_dlist *new)
{
	if (!lst || !new || *lst == new)
		return ;
	if (*lst)
	{
		if (ft_dlstlast(*lst) == new)
			new->prev->next = NULL;
		new->next = *lst;
		new->prev = NULL;
		(*lst)->prev = new;
		*lst = new;
		return ;
	}
	*lst = new;
	(*lst)->next = NULL;
	(*lst)->prev = NULL;
}
