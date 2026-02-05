/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 04:20:32 by pabellis          #+#    #+#             */
/*   Updated: 2025/12/12 03:20:22 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "render.h"

t_mat	*create_mat(t_vector *mat_vec, t_vector *tex_vec)
{
	t_mat	mat;

	if (mat_vec->max_elements == 0)
		vector_init(mat_vec, sizeof(t_mat));
	ft_bzero(&mat, sizeof(t_mat));
	mat.ni = 2.3f;
	mat.opacity = 1;
	mat.roughness_id.index = create_null_roughness(tex_vec);
	mat.ambient_id.index = create_null_ambient(tex_vec);
	mat.metalness_id.index = create_null_opacity(tex_vec);
	mat.normal_id.index = create_null_nmap(tex_vec);
	mat.opacity_id.index = create_null_opacity(tex_vec);
	mat.kd_id.index = create_null_texture(tex_vec);
	mat.name = NULL;
	if (vector_add(mat_vec, &mat, 1) == -1)
		return (NULL);
	return (get_last_vector_value(mat_vec));
}
