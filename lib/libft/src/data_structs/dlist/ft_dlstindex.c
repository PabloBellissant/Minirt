/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstindex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:50:10 by lucas             #+#    #+#             */
/*   Updated: 2025/03/08 07:36:07 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dlstindex(t_dlist *lst, t_dlist *to_find)
{
	int		i;

	if (!lst || !to_find)
		return (-2);
	i = 0;
	while (lst)
	{
		if (lst == to_find)
			return (i);
		lst = lst->next;
		i++;
	}
	return (-1);
}
