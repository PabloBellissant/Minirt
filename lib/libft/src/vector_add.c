/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 01:56:30 by pabellis          #+#    #+#             */
/*   Updated: 2025/02/12 03:33:36 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	vector_add(t_vector *vector, void *element)
{
	if (!vector || !element)
		return (-1);
	if (vector->num_elements + 1 == vector->max_elements)
	{
		if (vector_realloc(vector) == -1)
			return (-1);
	}
	ft_memcpy(vector->data + (vector->element_size * vector->num_elements),
		element, vector->element_size);
	vector->num_elements++;
	return (0);
}

int	vector_realloc(t_vector *vector)
{
	void	*new_data;

	new_data = malloc(vector->element_size * vector->max_elements * 2 + 1);
	if (new_data == NULL)
		return (-1);
	ft_memcpy(new_data, vector->data,
		vector->element_size * vector->num_elements);
	free(vector->data);
	vector->data = new_data;
	vector->max_elements *= 2;
	return (0);
}
