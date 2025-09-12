/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_bvh_full.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 04:59:45 by pabellis          #+#    #+#             */
/*   Updated: 2025/09/12 04:59:48 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	is_bvh_full(t_vector *bvh_vec, int *parents)
{
	size_t	i;
	int		orphin_count;

	orphin_count = 0;
	i = 0;
	while (i < bvh_vec->num_elements)
	{
		if (parents[i] == 0)
			++orphin_count;
		if (orphin_count == 2)
			return (false);
		++i;
	}
	return (true);
}
