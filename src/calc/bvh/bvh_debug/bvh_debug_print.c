/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_debug_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:59:28 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/09 00:46:57 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh_debug.h"

static inline int	calc_prefix_len(const char *pfx)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (pfx[i])
	{
		if ((unsigned char)pfx[i] >= 0x80)
		{
			len++;
			while ((unsigned char)pfx[i] >= 0x80)
				i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

void	print_leaf_info(int obj_id, size_t idx, t_align_info a,
			const char *pfx)
{
	int	current_width;
	int	spaces_needed;

	printf(C_LEAF_TAG" LEAF "C_RESET" "C_DIM"#"C_LEAF"%zu"C_RESET, idx);
	current_width = calc_prefix_len(pfx) + 4 + 8 + a.max_idx_width;
	spaces_needed = a.info_col - current_width;
	if (spaces_needed > 0)
		printf("%*s", spaces_needed, "");
	printf(C_SEPARATOR"│"C_RESET" "C_KEY"depth"C_RESET"="C_NUM_HIGHLIGHT
		"%-2d"C_RESET" "C_SEPARATOR"│"C_RESET, a.cur_depth);
	printf(" "C_KEY"obj_id"C_RESET"="C_NUM_HIGHLIGHT"%-6d"C_RESET" "
		C_SEPARATOR"│"C_RESET, obj_id);
	printf("                      "C_SEPARATOR"│ "C_RESET);
}

static inline void	print_node_children(const t_bvh_node *n)
{
	printf(" "C_KEY"children"C_RESET"="C_BRACKET"["C_NUM"%4d"C_DIM","
		C_NUM"%4d"C_BRACKET"]"C_RESET, n->children[0], n->children[1]);
	printf(" "C_SEPARATOR"│ "C_RESET);
}

void	print_node_info(const t_bvh_node *n, size_t idx, t_align_info a,
			const char *pfx)
{
	int	current_width;
	int	spaces_needed;

	printf(C_NODE_TAG" NODE "C_RESET" "C_DIM"#"C_NODE"%zu"C_RESET,
		idx);
	current_width = calc_prefix_len(pfx) + 4 + 8 + a.max_idx_width;
	spaces_needed = a.info_col - current_width;
	if (spaces_needed > 0)
		printf("%*s", spaces_needed, "");
	printf(C_SEPARATOR"│"C_RESET" "C_KEY"depth"C_RESET"="C_NUM_HIGHLIGHT
		"%-2d"C_RESET" "C_SEPARATOR"│"C_RESET, a.cur_depth);
	printf(" "C_KEY"skip"C_RESET"="C_NUM"%-8d"C_RESET
		" "C_SEPARATOR"│"C_RESET, n->skip);
	print_node_children(n);
}
