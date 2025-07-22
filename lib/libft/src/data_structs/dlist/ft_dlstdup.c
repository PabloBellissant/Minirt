/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:12:11 by lucas             #+#    #+#             */
/*   Updated: 2025/03/16 17:04:19 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstdup(const t_dlist *lst, void (*del)(void*))
{
	t_dlist	*dup;
	t_dlist	*new;
	void	*new_content;

	if (!lst)
		return (NULL);
	dup = NULL;
	while (lst)
	{
		new_content = NULL;
		if (lst->content)
			new_content = malloc(sizeof(lst->content));
		ft_memcpy(new_content, lst->content, sizeof(lst->content));
		new = ft_dlstnew(new_content);
		if (!new)
			return (free(new_content), ft_dlstclear(&dup, del), NULL);
		ft_dlstadd_back(&dup, new);
		lst = lst->next;
	}
	return (dup);
}
