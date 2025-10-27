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

t_mat	*create_mat(t_scene *scene)
{
	t_mat	mat;

	if (scene->mat.max_elements == 0)
		vector_init(&scene->mat, sizeof(t_mat));
	ft_bzero(&mat, sizeof(t_mat));
	if (vector_add(&scene->mat, &mat, 1) == -1)
		return (NULL);
	return (get_last_vector_value(&scene->mat));
}
