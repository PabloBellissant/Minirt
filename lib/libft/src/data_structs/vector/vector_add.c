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

#include "libft.h"

int	vector_add(t_vector *vector, void *element, size_t elem_count)
{
	void	*actual;

	if (vector->num_elements + elem_count >= vector->max_elements)
	{
		if (set_vector_size(vector, vector->num_elements + elem_count) == -1)
			return (-1);
	}
	actual = (char *)vector->data
		+ (vector->element_size * vector->num_elements);
	ft_memcpy(actual, element, vector->element_size * elem_count);
	vector->num_elements += elem_count;
	return (0);
}
