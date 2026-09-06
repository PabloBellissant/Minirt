/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_obb.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:18:43 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/05 01:45:25 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_OBB_H
# define BVH_OBB_H

# define EIGH_TOL 1.0e-9f
# define EIGH_MAX_ROT 45

/*
	t_vec3 axes[3] in t_bvh_obb to avoid calling it often
	(would not be necessary in GPU struct imo)
*/
typedef struct s_bvh_obb
{
	t_vec3	center;
	t_vec4	q;
	t_vec3	half_extents;
	t_vec3	axes[3];
}			t_bvh_obb;

static inline t_vec3	quat_rotate_vec3(const t_vec4 q, const t_vec3 v)
{
	const t_vec3	u = vec3(q.x, q.y, q.z);
	const float		s = q.w;
	const t_vec3	t = vec3_scale(vec3_cross(u, v), 2.0f);

	return (vec3_add(v, vec3_add(vec3_scale(t, s), vec3_cross(u, t))));
}

static inline void	obb_axes_from_quat(const t_vec4 q_in, t_vec3 axis[3])
{
	const t_vec4	q = vec4_normalize(q_in);

	axis[0] = quat_rotate_vec3(q, vec3(1.f, 0.f, 0.f));
	axis[1] = quat_rotate_vec3(q, vec3(0.f, 1.f, 0.f));
	axis[2] = quat_rotate_vec3(q, vec3(0.f, 0.f, 1.f));
}

t_vec3		pca_mean_objects(t_vector objs, size_t *out_n);
t_mat3		get_pca_covariance_objects(const t_vector objs,
							const t_vec3 mean, const size_t n_points);
t_vec4		quat_from_mat3_cols(t_mat3 m);

void		mat3_eigh_jacobi(t_mat3 a, float evals[3], t_mat3 *evecs);

t_cuboid	mat3_project_objects(t_vector objs, t_mat3 basis, t_vec3 origin);

t_mat3		basis3_from_eigh(t_mat3 evecs, const float evals[3]);

t_vec3		get_obb_projected_spread(t_bvh_obb obb, t_vector primitives);

#endif//BVH_OBB_H
