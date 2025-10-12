/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 21:17:04 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/11 21:17:06 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

ssize_t	partition(void *array, ssize_t high, ssize_t elem_size,
			int (*compare_function)(const void *, const void *));
void	quick_sort_recur(void *array, ssize_t high, ssize_t elem_size,
			int (*compare_function)(const void *, const void *));

void	quick_sort(void *array, size_t elem_count, size_t elem_size,
	int (*compare_function)(const void *, const void *))
{
	quick_sort_recur(array, (ssize_t) elem_count, (ssize_t) elem_size,
		compare_function);
}

void	quick_sort_recur(void *array, ssize_t high, ssize_t elem_size,
	int (*compare_function)(const void *, const void *))
{
	ssize_t	pi;

	if (high > 0)
	{
		pi = partition(array, high, elem_size, compare_function);
		quick_sort_recur(array, pi - 1, elem_size, compare_function);
		quick_sort_recur((char *)array + ((pi + 1) * elem_size),
			high - (pi + 1), elem_size, compare_function);
	}
}

void	*get_elem(void *array, ssize_t elem_size, ssize_t elem_num)
{
	return ((char *)array + (elem_size * elem_num));
}

void	swap_mem(void *array, ssize_t index_a,
	ssize_t index_b, ssize_t elem_size)
{
	char	bit;
	ssize_t	i;
	char	*a_char;
	char	*b_char;

	a_char = (char *)get_elem(array, elem_size, index_a);
	b_char = (char *)get_elem(array, elem_size, index_b);
	i = 0;
	while (i < elem_size)
	{
		bit = a_char[i];
		a_char[i] = b_char[i];
		b_char[i] = bit;
		++i;
	}
}

ssize_t	partition(void *array, ssize_t high, ssize_t elem_size,
	int (*compare_function)(const void *, const void *))
{
	ssize_t	i;
	ssize_t	j;

	i = -1;
	j = 0;
	while (j < high)
	{
		if (compare_function(get_elem(array, elem_size, j),
				get_elem(array, elem_size, high)) < 0)
		{
			++i;
			swap_mem(array, i, j, elem_size);
		}
		++j;
	}
	swap_mem(array, i + 1, high, elem_size);
	return (i + 1);
}
