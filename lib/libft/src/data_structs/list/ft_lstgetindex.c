/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstgetindex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 02:11:52 by jaubry--          #+#    #+#             */
/*   Updated: 2025/03/27 02:36:24 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstgetindex(t_list *lst, size_t index)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		if (i == index)
			return (lst);
		i++;
		lst = lst->next;
	}
	return (NULL);
}
