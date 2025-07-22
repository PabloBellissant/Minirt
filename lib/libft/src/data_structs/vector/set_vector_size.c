/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_vector_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:51:24 by pabellis          #+#    #+#             */
/*   Updated: 2025/04/14 17:51:28 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	get_round_size(size_t size);

int	set_vector_size(t_vector *vector, size_t size)
{
	void	*new_data;
	size_t	round_size;

	round_size = get_round_size(size);
	if (vector->max_elements == 0)
	{
		vector->data = malloc(vector->element_size * round_size);
		if (!vector->data)
			return (-1);
		vector->max_elements = round_size;
		return (0);
	}
	new_data = malloc(vector->element_size * round_size);
	if (new_data == NULL)
		return (-1);
	ft_memcpy(new_data, vector->data,
		vector->element_size * vector->num_elements);
	free(vector->data);
	vector->data = new_data;
	vector->max_elements = round_size;
	return (0);
}

static size_t	get_round_size(size_t size)
{
	size_t	new_size;

	new_size = VECTOR_BASE_SIZE;
	while (new_size < size)
		new_size *= 2;
	return (new_size);
}
