/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarcucc <lmarcucc42lyon.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:34:42 by lmarcucc          #+#    #+#             */
/*   Updated: 2025/03/16 17:04:37 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstmap(t_dlist *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*tmp_content;
	t_dlist	*first;
	t_dlist	*new;

	first = NULL;
	if (!f || !del || !lst)
		return (NULL);
	while (lst)
	{
		tmp_content = f(lst->content);
		if (!tmp_content)
			return (ft_dlstclear(&first, del), first);
		new = ft_dlstnew(tmp_content);
		if (!new)
		{
			del(tmp_content);
			return (ft_dlstclear(&first, del), first);
		}
		ft_dlstadd_back(&first, new);
		lst = lst->next;
	}
	return (first);
}
