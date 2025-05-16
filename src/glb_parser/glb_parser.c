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

t_object	*glb_parser(char *str)
{
	t_vector	object_vector;
	//t_object	object;

	vector_init(&object_vector, sizeof(t_object));
	(void) str;
	return (0);
}