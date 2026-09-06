/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_bounds_obb.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 23:11:04 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/04 23:08:14 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include <math.h>
#include "mat3_vec3.h"
#include "vec3_constructors.h"
#include "vec3_operations.h"

static inline t_mat3	apply_eigh_jacobi(const t_vector objs, t_vec3 *mean)
{
	float		evals[3];
	t_mat3		evecs;
	size_t		n;
	t_mat3		cov;

	*mean = pca_mean_objects(objs, &n);
	cov = get_pca_covariance_objects(objs, *mean, n);
	mat3_eigh_jacobi(cov, evals, &evecs);
	return (basis3_from_eigh(evecs, evals));
}

static inline void	obb_from_pca(t_bvh_obb *obb, const t_vector objs)
{
	t_mat3		basis;
	t_cuboid	extent;
	t_vec3		mean;

	basis = apply_eigh_jacobi(objs, &mean);
	extent = mat3_project_objects(objs, basis, mean);
	if (!cuboid_isfinite(extent))
	{
		obb->center = mean;
		obb->half_extents = vec3_zero();
		obb->q = quat_identity();
		obb_axes_from_quat(obb->q, obb->axes);
		return ;
	}
	obb->half_extents = cuboid_half(extent);
	obb->center = vec3_add(mean, mat3_mul_vec3(basis,
				cuboid_center(extent)));
	obb->q = quat_from_mat3_cols(basis);
	obb_axes_from_quat(obb->q, obb->axes);
}

void	evaluate_bounds_obb(t_bvh_obb *new, const t_vector primitives)
{
	*new = (t_bvh_obb){0};
	if (primitives.num_elements == 0)
	{
		new->center = vec3_zero();
		new->half_extents = vec3_zero();
		new->q = quat_identity();
		obb_axes_from_quat(new->q, new->axes);
		return ;
	}
	obb_from_pca(new, primitives);
}
