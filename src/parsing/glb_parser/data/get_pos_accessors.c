/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pos_accessors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 03:57:22 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/30 03:57:23 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json.h"
#include "glb.h"

int	get_pos_accessors(t_json *json, int object_id)
{
	int	mesh_id;

	mesh_id = get_mesh_id(json, object_id);
	json = get_by_key_name(json, "meshes");
	if (!json || !json->child || mesh_id == -1)
		return (-1);
	json = json->child;
	while (mesh_id > 0)
	{
		json = json->next;
		--mesh_id;
	}
	json = json->child;
	if (!json)
		return (-1);
	json = get_by_key_name(json, "primitives");
	if (!json || !json->child || !json->child->child)
		return (-1);
	json = json->child->child->child;
	if (!json)
		return (-1);
	json = get_by_key_name(json, "POSITION");
	if (!json || json->type != JSON_NUMBER)
		return (-1);
	return (json->number);
}
