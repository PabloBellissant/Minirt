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

#include "libft.h"

void	vector_init(t_vector *vector, size_t element_size)
{
	vector->element_size = element_size;
	vector->max_elements = 0;
	vector->num_elements = 0;
	vector->data = NULL;
}
