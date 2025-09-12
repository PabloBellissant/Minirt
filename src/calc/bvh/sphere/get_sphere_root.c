/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_root.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 05:00:12 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/12 05:00:14 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bvh.h"

t_sphere_bvh	*get_sphere_root(t_vector *bvh_vec, int *parents)
{
	size_t		i;
	t_sphere_bvh	*bvh;

	bvh = bvh_vec->data;
	i = 0;
	while (parents[i] == 1)
		++i;
	return (&bvh[i]);
}
