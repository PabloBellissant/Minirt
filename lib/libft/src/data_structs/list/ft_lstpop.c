/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:34:28 by jaubry--          #+#    #+#             */
/*   Updated: 2025/04/10 19:19:41 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpop(t_list **lst, t_list **el, void (*del)(void *))
{
	t_list	*cur;
	t_list	*prev;

	if (lst)
	{
		prev = NULL;
		cur = *lst;
		while (cur)
		{
			if (cur == *el)
			{
				if (!prev)
					*lst = cur->next;
				else
					prev->next = cur->next;
				*el = cur->next;
				ft_lstdelone(cur, del);
				break ;
			}
			prev = cur;
			cur = cur->next;
		}
	}
}
