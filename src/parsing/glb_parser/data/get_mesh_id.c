/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mesh_id.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 03:32:44 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/30 03:32:46 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json.h"

int	get_mesh_id(t_json *json, int object_id)
{
	t_json	*object;

	object = get_by_key_name(json, "nodes");
	if (!object || !object->child)
		return (-1);
	object = object->child;
	while (object_id > 0)
	{
		object = object->next;
		object_id--;
	}
	object = object->child;
	object = get_by_key_name(object, "mesh");
	if (!object || object->type != JSON_NUMBER)
		return (-1);
	return (object->number);
}
