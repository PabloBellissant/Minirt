/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:36:57 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 19:16:19 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_click_inside(t_vec2i pos, t_vec2i screen_size,
			t_hbranch *ondisplay_ui)
{
	return ((pos.x > 0)
		&& (pos.y > 0)
		&& (pos.x < screen_size.x)
		&& (pos.y < screen_size.y)
		&& !is_inside_comp(ondisplay_ui, pos));
}

static inline void	ft_swap(int *a, int *b)
{
	const int	temp = *a;

	*a = *b;
	*b = temp;
}

void	rearrange_order(t_vec2i *mouse_pos)
{
	if (mouse_pos[START].x > mouse_pos[END].x)
		ft_swap(&mouse_pos[START].x, &mouse_pos[END].x);
	if (mouse_pos[START].y > mouse_pos[END].y)
		ft_swap(&mouse_pos[START].y, &mouse_pos[END].y);
}

void	select_mouse_pos(t_vec2i mouse_pos[2], t_mlx *mlx_data)
{
	if ((mouse_pos[START].x != 0) && (mouse_pos[START].y != 0))
		mouse_pos[END] = mlx_data->mouse_input.pos;
}
