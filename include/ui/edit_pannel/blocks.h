/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:58:03 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 18:22:57 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOCKS_H
# define BLOCKS_H

typedef struct s_block_util
{
	int				*y_size;
	t_hbranch		*comp;
	t_data			*data;
	char			*name;
	union
	{
		float		*f_ptr;
		cl_float	*clf_ptr;
		t_vec3		*v_ptr;
		t_texture	*tex_ptr;
		t_rgb		*rgb_ptr;
	};
}				t_block_util;

// Building blocks
t_hbranch	*add_block_title(t_block_util bl);
t_hbranch	*add_form_block(t_block_util bl);
t_hbranch	*add_edit_block(t_hbranch *edit_zone, int *y_size);
t_hbranch	*add_edit_pannel_title(t_hbranch *obj_edit, int *y_size,
				char *title);

// Forms
int			add_float_edit(t_block_util bl);
int			add_vec3_edit(t_block_util bl);

// Sliders
int			add_grayscale_edit(t_block_util bl);
int			add_slider_edit(t_block_util bl, float start,
				float stop, bool linear);

// Colorpicker
int			add_color_edit(t_block_util bl);
int			add_texture_edit(t_block_util bl);

#endif//BLOCKS_H
