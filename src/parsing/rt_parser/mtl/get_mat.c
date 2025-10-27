/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:04:44 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/21 21:04:45 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_mat	*get_mat(const char *mat_name, t_vector *mat)
{
	size_t	i;
	t_mat	*actual;

	actual = mat->data;
	i = 0;
	while (i < mat->num_elements)
	{
		if (ft_strcmp(mat_name, actual[i].name) == 0)
			return (&actual[i]);
		++i;
	}
	return (NULL);
}
