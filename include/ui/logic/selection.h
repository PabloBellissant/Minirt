/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:36:37 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 18:03:59 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECTION_H
# define SELECTION_H

# define START	0
# define END	1

void	select_obj(t_data *data, t_object *obj);
void	clear_selected(t_data *data);

void	draw_select(t_vec2i mouse_pos[2], t_mlx *mlx_data);

void	select_zone(t_vec2i pos, t_maction action,
			t_data *data, t_mlx *mlx_data);

void	update_scene_select(t_data *data, t_object *obj);
void	clear_scene_select(t_data *data, t_object *obj);

bool	is_click_inside(t_vec2i pos, t_vec2i screen_size,
			t_hbranch *ondisplay_ui);
void	rearrange_order(t_vec2i *mouse_pos);
void	select_mouse_pos(t_vec2i mouse_pos[2], t_mlx *mlx_data);

typedef struct s_selection
{
	t_vec2i		mouse_pos[2];	//start and stop
	t_vector	selected;		// object *
}				t_selection;

#endif//SELECTION_H
