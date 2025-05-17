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

	(void) str;
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

static void	print_json(t_json *json, int depth)
{
	int	i = 0;
	while (i++ < depth)
		dprintf(2, "    ");
	dprintf(2, "Key : %s, type : %d\n", json->key, json->type);
	if (json->type == JSON_OBJECT)
		print_json(json->child, depth + 1);
	if (json->next)
		print_json(json->next, depth);
}
