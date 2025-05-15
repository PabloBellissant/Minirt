/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 03:38:00 by pabellis          #+#    #+#             */
/*   Updated: 2025/03/25 00:23:15 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

#define INIT_SIZE 100

int	vector_init(t_vector *vector, size_t element_size)
{
	vector->element_size = element_size;
	vector->max_elements = INIT_SIZE;
	vector->num_elements = 0;
	vector->data = malloc(element_size * INIT_SIZE);
	if (vector->data == NULL)
		return (-1);
	return (0);
}
