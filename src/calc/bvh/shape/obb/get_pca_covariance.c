/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pca_covariance.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:42:58 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 12:09:57 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"
#include "matrices.h"
#include "bvh.h"

static inline void	pca_sum_cov_point(t_mat3 *cov, const t_vec3 d)
{
	cov->m[0][0] += d.x * d.x;
	cov->m[0][1] += d.x * d.y;
	cov->m[0][2] += d.x * d.z;
	cov->m[1][0] += d.y * d.x;
	cov->m[1][1] += d.y * d.y;
	cov->m[1][2] += d.y * d.z;
	cov->m[2][0] += d.z * d.x;
	cov->m[2][1] += d.z * d.y;
	cov->m[2][2] += d.z * d.z;
}

static inline void	pca_sum_cov_triangle(t_mat3 *cov, const t_vec3 mean,
						const t_triangle tri)
{
	pca_sum_cov_point(cov, vec3_sub(tri.p0.pos, mean));
	pca_sum_cov_point(cov, vec3_sub(tri.p1.pos, mean));
	pca_sum_cov_point(cov, vec3_sub(tri.p2.pos, mean));
}

static inline void	pca_sum_cov_objects(t_mat3 *cov, const t_vec3 mean,
						const t_object o)
{
	if (o.type == TRIANGLE)
		pca_sum_cov_triangle(cov, mean, o.triangle);
	else
		pca_sum_cov_point(cov, vec3_sub(o.centroid, mean));
}

static inline void	pca_inv_cov_point(t_mat3 *cov, const float inv)
{
	cov->m[0][0] *= inv;
	cov->m[0][1] *= inv;
	cov->m[0][2] *= inv;
	cov->m[1][0] *= inv;
	cov->m[1][1] *= inv;
	cov->m[1][2] *= inv;
	cov->m[2][0] *= inv;
	cov->m[2][1] *= inv;
	cov->m[2][2] *= inv;
}

t_mat3	get_pca_covariance_objects(const t_vector objs, const t_vec3 mean,
			const size_t n_points)
{
	t_object	*o;
	t_mat3		cov;
	size_t		i;

	cov = mat3_zero();
	o = (t_object *)objs.data;
	i = 0;
	while (i < objs.num_elements)
	{
		pca_sum_cov_objects(&cov, mean, o[i]);
		i++;
	}
	if (n_points == 0)
		return (cov);
	pca_inv_cov_point(&cov, 1.0f / (float)n_points);
	return (cov);
}
