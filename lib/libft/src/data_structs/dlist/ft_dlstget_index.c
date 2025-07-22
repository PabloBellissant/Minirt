/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstget_index.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 06:57:15 by lucas             #+#    #+#             */
/*   Updated: 2025/03/08 07:35:57 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstget_index(t_dlist *lst, size_t index)
{
	size_t	i;

	if (!lst)
		return (NULL);
	i = 0;
	while (lst)
	{
		if (i == index)
			return (lst);
		lst = lst->next;
		i++;
	}
	return (NULL);
}
