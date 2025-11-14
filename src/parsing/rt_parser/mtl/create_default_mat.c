/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_default_mat.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 02:37:15 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/22 02:37:16 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"

t_mat	create_default_mat(void)
{
	t_mat	mat;

	ft_bzero(&mat, sizeof(t_mat));
	mat.kd = vec3(0.752f, 0.606f, 0.226f);
	mat.ks = vec3(0.628f, 0.556f, 0.366f);
	mat.ns = 55.2f;
	mat.ni = 2.3f;
	return (mat);
}
