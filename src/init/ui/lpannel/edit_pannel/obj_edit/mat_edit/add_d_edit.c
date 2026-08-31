/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_d_edit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:08:46 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 20:34:09 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	**`d` (Dissolve/Opacity)** - **0.0 to 1.0**
	- 0.0 = fully transparent
	- 1.0 = fully opaque
*/
int	add_d_edit(t_data *data, t_hbranch *obj_edit, int *y_size, t_mat *mat)
{
	t_texture		*tex;
	int				ret;
	t_block_util	bl;

	ret = 0;
	tex = get_vector_value(&data->scene.texture, mat->opacity_id.index);
	if (is_tex_editable(tex))
	{
		bl = (t_block_util){.data = data, .comp = obj_edit, .y_size = y_size,
			.tex_ptr = tex, .name = "Opacity"};
		ret = add_grayscale_edit(bl);
	}
	return (ret);
}
