/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 04:20:32 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/21 05:52:29 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "render.h"

t_mat	*create_mat(t_vector *vec)
{
	t_mat	mat;

	if (vec->max_elements == 0)
		vector_init(vec, sizeof(t_mat));
	ft_bzero(&mat, sizeof(t_mat));
	mat.ni = 2.3f;
	mat.kd = vec3(1, 1, 1);
	mat.opacity = 1;
	mat.pr = 1;
	if (vector_add(vec, &mat, 1) == -1)
		return (NULL);
	return (get_last_vector_value(vec));
}
