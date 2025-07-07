/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vertex_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 02:42:57 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/30 02:42:59 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json.h"

int	get_vertex_count(t_json *json, int accessors_id)
{
	if (accessors_id == -1)
		return (0);
	json = get_by_key_name(json, "accessors");
	if (json)
		json = json->child;
	if (json && json->type != JSON_OBJECT)
		return (-1);
	while (accessors_id > 0)
	{
		--accessors_id;
		json = json->next;
	}
	if (json->type != JSON_OBJECT)
		return (-1);
	json = json->child;
	json = get_by_key_name(json, "count");
	if (json && json->type == JSON_NUMBER)
		return (json->number);
	return (-1);
}
