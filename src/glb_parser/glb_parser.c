/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glb_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 02:48:09 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/16 02:48:11 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "struct.h"
#include "glb.h"
#include "json.h"

static void	print_json(t_json *json, int depth);

t_object	*glb_parser(char *str)
{
	t_vector	object_vector;
	t_object	object;
	int			object_count;
	int			i;
	t_json		*json;

	object_count = 2;
	vector_init(&object_vector, sizeof(t_object));
	json = json_parser(str);
	print_json(json, 0);
	i = 0;
	while (i < object_count)
	{
		if (vector_add(&object_vector, &object, 1) == -1)
			return (NULL);
		++i;
	}
	return (0);
}

static void	print_array(t_json *json, int depth)
{
	int	i = 0;
	while (i++ < depth)
		dprintf(2, "    ");
	if (json->type == JSON_NULL)
		dprintf(2, "null\n");
	else if (json->type == JSON_NUMBER)
		dprintf(2, "%f\n", json->number);
	else if (json->type == JSON_STRING)
		dprintf(2, "%s\n", json->string);
	else if (json->type == JSON_BOOL)
		dprintf(2, "%s\n", json->boolean ? "true" : "false");
	else if (json->type == JSON_ARRAY)
		print_array(json, depth);
	else if (json->type == JSON_OBJECT)
		print_json(json->child, depth);
	if (json->next)
		print_array(json->next, depth);
}

static void	print_json(t_json *json, int depth)
{
	int	i = 0;
	while (i++ < depth)
		dprintf(2, "    ");
	dprintf(2, "%s : ", json->key);
	if (json->type == JSON_NULL)
		dprintf(2, "null\n");
	else if (json->type == JSON_NUMBER)
		dprintf(2, "%f\n", json->number);
	else if (json->type == JSON_STRING)
		dprintf(2, "%s\n", json->string);
	else if (json->type == JSON_BOOL)
		dprintf(2, "%s\n", json->boolean ? "true" : "false");
	else if (json->type == JSON_ARRAY)
	{
		dprintf(2, "\n");
		print_array(json->child, depth + 1);
	}
	else if (json->type == JSON_OBJECT)
	{
		dprintf(2, "\n");
		print_json(json->child, depth + 1);
	}
	if (json->next)
		print_json(json->next, depth);
}
