/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_realloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 03:58:33 by pabellis          #+#    #+#             */
/*   Updated: 2025/04/08 03:58:36 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	vector_realloc(t_vector *vector)
{
	void	*new_data;

	if (vector->max_elements == 0)
	{
		vector->data = malloc(vector->element_size * VECTOR_BASE_SIZE);
		if (!vector->data)
			return (-1);
		vector->max_elements = VECTOR_BASE_SIZE;
		return (0);
	}
	new_data = malloc(vector->element_size * vector->max_elements * 2);
	if (new_data == NULL)
		return (-1);
	ft_memcpy(new_data, vector->data,
		vector->element_size * vector->num_elements);
	free(vector->data);
	vector->data = new_data;
	vector->max_elements *= 2;
	return (0);
}
