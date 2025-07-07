/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 05:37:52 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/29 05:37:54 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json.h"

int	get_object_count(t_json *json)
{
	int	i;

	json = get_by_key_name(json, "nodes");
	if (!json || json->type != JSON_ARRAY)
		return (0);
	json = json->child;
	i = 0;
	while (json)
	{
		++i;
		json = json->next;
	}
	return (i);
}