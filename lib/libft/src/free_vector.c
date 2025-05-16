/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:10:58 by pabellis          #+#    #+#             */
/*   Updated: 2025/03/17 07:11:02 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	free_vector(t_vector *vector)
{
	vector->max_elements = 0;
	vector->num_elements = 0;
	vector->element_size = 0;
	free(vector->data);
	vector->data = NULL;
}
