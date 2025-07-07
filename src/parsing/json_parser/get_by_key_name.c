/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_by_key_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 00:48:16 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/29 00:48:18 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "json.h"

t_json	*get_by_key_name(t_json *node, char *name)
{
	while (node)
	{
		if (ft_strcmp(node->key, name) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}
