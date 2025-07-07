/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_vector_elem.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 01:00:01 by pabellis          #+#    #+#             */
/*   Updated: 2025/04/22 01:00:24 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	remove_vector_elem(t_vector *vector, size_t i)
{
	void	*pointer;

	pointer = get_vector_value(vector, i);
	if (i + 1 == vector->num_elements)
		ft_bzero(pointer, vector->element_size);
	else
	{
		ft_memmove(pointer,
			(char *)pointer + vector->element_size,
			vector->element_size * (vector->num_elements - i - 1));
	}
	--vector->num_elements;
}
