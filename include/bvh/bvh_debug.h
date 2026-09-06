/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh_debug.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:58:19 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/09 00:51:00 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_DEBUG_H
# define BVH_DEBUG_H

# include "bvh.h"

# define MAX_PRINT_SIZE 512

# define C_RESET			"\033[0m"
# define C_BG_DARK			"\033[48;5;233m"
# define C_HEADER			"\033[1;3;38;5;141;48;5;235m"
# define C_TITLE			"\033[1;38;5;177m"
# define C_LEAF				"\033[1;38;5;78m"
# define C_LEAF_TAG			"\033[38;5;235;48;5;78m"
# define C_NODE				"\033[1;38;5;111m"
# define C_NODE_TAG			"\033[38;5;233;48;5;111m"
# define C_TREE				"\033[38;5;240m"
# define C_NUM				"\033[38;5;211m"
# define C_NUM_HIGHLIGHT	"\033[1;38;5;212m"
# define C_LABEL			"\033[3;38;5;80m"
# define C_VALUE			"\033[38;5;252m"
# define C_DIM				"\033[2;38;5;239m"
# define C_BRACKET			"\033[38;5;240m"
# define C_SEPARATOR		"\033[38;5;235m"
# define C_KEY				"\033[38;5;204m"
# define C_PERCENT			"\033[2;38;5;177m"
# define C_BORDER			"\033[38;5;240m"

typedef struct s_align_info
{
	t_bvh_header	*h;
	int				max_depth;
	int				max_idx_width;
	int				base_padding;
	int				info_col;
	int				cur_depth;
}	t_align_info;

typedef struct s_tree_context
{
	t_bvh_header	*header;
	t_align_info	align;
	int				depth;
	bool			is_last;
}	t_tree_context;

void	debug_bvh_tree(t_bvh_header *h);
void	print_bvh_debug_header(void);
void	print_bvh_node_tree(t_bvh_header *h);
void	print_bvh_config(t_bvh_header *h);
void	print_bvh_stats(t_bvh_header *h);
void	calc_align_info(const t_bvh_header *h, t_align_info *info);
void	print_node_info(const t_bvh_node *n, size_t idx, t_align_info a,
			const char *pfx);
void	print_leaf_info(int obj_id, size_t idx, t_align_info a,
			const char *pfx);
void	print_bounds(const t_bvh_bounds *b, const t_bvh_shape shape);
int		get_num_width(size_t num);

#endif
