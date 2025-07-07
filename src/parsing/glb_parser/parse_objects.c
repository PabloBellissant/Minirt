/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 06:14:40 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/29 06:14:42 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct.h"
#include "json.h"
#include "glb.h"

static t_obj	get_object(t_json *json_nodes, int id, void *binary);
static t_vec3	get_vec3(t_json *json);
static t_vec4	get_vec4(t_json *json);

t_obj	*parse_objects(t_json *json, void *binary)
{
	int			i;
	int			object_count;
	t_obj		*object_list;

	object_count = get_object_count(json);
	object_list = malloc(sizeof(t_obj) * object_count);
	if (!object_list)
		return (NULL);
	i = 0;
	while (i < object_count)
	{
		object_list[i] = get_object(json, i, binary);
		++i;
	}
	return (object_list);
}

static t_obj	set_object_data(t_json *object_json)
{
	t_obj	object;
	// t_json	*temp;

	ft_bzero(&object, sizeof(t_obj));
	object.pos = get_vec3(get_by_key_name(object_json, "translation"));
	object.rot = get_vec4(get_by_key_name(object_json, "rotation"));
	object.scale = get_vec3(get_by_key_name(object_json, "scale"));
	// temp = get_by_key_name(object_json, "name");
	// if (temp && temp->type == JSON_STRING)
	// 	object.name = temp->string;
	return (object);
}

static t_obj	get_object(t_json *json, int id, void *binary)
{
	t_obj	object;
	t_json		*node;
	int			i;

	ft_bzero(&object, sizeof(t_obj));
	node = get_by_key_name(json, "nodes");
	if (!node || !node->child)
		return (object);
	node = node->child;
	i = 0;
	while (i < id)
	{
		node = node->next;
		++i;
	}
	node = node->child;
	object = set_object_data(node);
	object.vertex_count = get_vertex_count(json, get_pos_accessors(json, id));
	object.vertex = get_vertex(json, binary, id);
	return (object);
}

static t_vec3	get_vec3(t_json *json)
{
	t_vec3	vec3;

	ft_bzero(&vec3, sizeof(t_vec3));
	if (!json || !json->child)
		return (vec3);
	json = json->child;
	vec3.x = json->number;
	json = json->next;
	if (!json)
		return (vec3);
	vec3.y = json->number;
	json = json->next;
	if (!json)
		return (vec3);
	vec3.z = json->number;
	return (vec3);
}

static t_vec4	get_vec4(t_json *json)
{
	t_vec4	vec4;

	ft_bzero(&vec4, sizeof(t_vec4));
	if (!json || !json->child)
		return (vec4);
	json = json->child;
	vec4.x = json->number;
	json = json->next;
	if (!json)
		return (vec4);
	vec4.y = json->number;
	json = json->next;
	if (!json)
		return (vec4);
	vec4.z = json->number;
	json = json->next;
	if (!json)
		return (vec4);
	vec4.w = json->number;
	return (vec4);
}
