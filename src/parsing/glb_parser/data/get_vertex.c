/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vertex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 05:22:13 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/30 05:22:16 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "json.h"
#include "glb.h"

static t_vertex	*parse_vertex_array(void *data, int nbr);
static int		get_offset(t_json *node);
static int		get_data_len(t_json *node);

t_vertex	*get_vertex(t_json *json, void *binary, int id)
{
	t_vertex	*vertex;
	t_json		*node;
	int			buffer_pos;

	buffer_pos = get_pos_accessors(json, id);
	node = get_by_key_name(json, "bufferViews");
	if (buffer_pos == -1 || node == NULL || !node->child)
		return (NULL);
	node = node->child;
	while (node && id > 0)
	{
		node = node->next;
		--id;
	}
	if (!node)
		return (NULL);
	vertex = parse_vertex_array(binary + get_offset(node), get_data_len(node));
	return (vertex);
}

static int	get_offset(t_json *node)
{
	node = node->child;
	if (!node)
		return (0);
	node = get_by_key_name(node, "byteOffset");
	if (!node || node->type != JSON_NUMBER)
		return (0);
	return (node->number);
}

static int	get_data_len(t_json *node)
{
	node = node->child;
	if (!node)
		return (0);
	node = get_by_key_name(node, "byteLength");
	if (!node || node->type != JSON_NUMBER)
		return (0);
	return (node->number);
}

static t_vertex	*parse_vertex_array(void *data, int nbr)
{
	t_vertex	*array;
	int			i;
	float		tmp;

	nbr /= 3;
	array = malloc(sizeof(t_vertex) * nbr);
	if (!array)
		return (NULL);
	i = 0;
	while (i < nbr)
	{
		ft_memcpy(&tmp, data + i * 12 + 0, 4);
		array[i].pos.x = (float)tmp;
		ft_memcpy(&tmp, data + i * 12 + 4, 4);
		array[i].pos.y = (float)tmp;
		ft_memcpy(&tmp, data + i * 12 + 8, 4);
		array[i].pos.z = (float)tmp;
		// array[i].u = 0.0f;
		// array[i].v = 0.0f;
		++i;
	}
	return (array);
}
