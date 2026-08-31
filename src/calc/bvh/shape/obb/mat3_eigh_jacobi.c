/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3_eigh_jacobi.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:45:25 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/02 23:20:27 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mat3_jacobi_ops.h"
#include "matrices.h"
#include "bvh.h"

void	mat3_eigh_jacobi(t_mat3 a, float evals[3], t_mat3 *evecs)
{
	t_mat3				m;
	t_jacobi_rot_params	r;
	int					i;

	m = a;
	*evecs = mat3_identity();
	i = 0;
	while (i < EIGH_MAX_ROT)
	{
		r = get_mat3_jacobi_rot_params(m);
		if (r.amax < EIGH_TOL)
			break ;
		mat3_jacobi_apply(&m, evecs, r);
		i++;
	}
	evals[0] = m.m[0][0];
	evals[1] = m.m[1][1];
	evals[2] = m.m[2][2];
}
