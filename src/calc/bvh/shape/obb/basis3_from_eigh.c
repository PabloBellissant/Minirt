/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basis3_from_eigh.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 22:47:30 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/04 23:08:38 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "mat3_accessors.h"
#include "mat3_constructors.h"
#include "vec3_normalize.h"
#include "vec3_products.h"

static inline void	ft_swap(int *a, int *b)
{
	const int	tmp = *a;

	*a = *b;
	*b = tmp;
}

static inline void	sort3_desc(const float e[3], int idx[3])
{
	idx[0] = 0;
	idx[1] = 1;
	idx[2] = 2;
	if (e[idx[0]] < e[idx[1]])
		ft_swap(idx + 0, idx + 1);
	if (e[idx[1]] < e[idx[2]])
		ft_swap(idx + 1, idx + 2);
	if (e[idx[0]] < e[idx[1]])
		ft_swap(idx + 0, idx + 1);
}

t_mat3	basis3_from_eigh(t_mat3 evecs, const float evals[3])
{
	int		idx[3];
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;

	sort3_desc(evals, idx);
	u = vec3_normalize_safe(mat3_get_col(evecs, idx[0]));
	v = vec3_normalize_safe(mat3_get_col(evecs, idx[1]));
	w = vec3_normalize_safe(vec3_cross(u, v));
	v = vec3_normalize_safe(vec3_cross(w, u));
	return (mat3_from_cols(u, v, w));
}
