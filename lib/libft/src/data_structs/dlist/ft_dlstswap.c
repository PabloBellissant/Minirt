/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstswap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:44:39 by lucas             #+#    #+#             */
/*   Updated: 2025/03/08 07:36:16 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstswap(t_dlist *l1, t_dlist *l2)
{
	void	*tmp;

	if (!l1 || !l2 || l1 == l2)
		return ;
	tmp = l1->content;
	l1->content = l2->content;
	l2->content = tmp;
}
