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
	mat.ni = 1.3f;
	return (mat);
}
