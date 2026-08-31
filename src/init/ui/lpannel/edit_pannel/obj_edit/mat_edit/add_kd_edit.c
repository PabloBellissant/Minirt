/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_kd_edit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:12:19 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 20:35:50 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	**`Kd` (Diffuse Color)** - **0.0 to 1.0** per RGB channel
	- RGB values between 0.0 and 1.0
*/
int	add_kd_edit(t_data *data, t_hbranch *obj_edit, int *y_size, t_mat *mat)
{
	t_texture		*tex;
	int				ret;
	t_block_util	bl;

	ret = 0;
	tex = get_vector_value(&data->scene.texture, mat->kd_id.index);
	if (is_tex_editable(tex))
	{
		bl = (t_block_util){.data = data, .comp = obj_edit,
			.y_size = y_size, .tex_ptr = tex, .name = "Diffuse"};
		ret = add_texture_edit(bl);
	}
	return (ret);
}
