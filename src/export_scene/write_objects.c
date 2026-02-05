/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:48:39 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/05 00:48:39 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define OBJECT_COMMENT "# Custom .obj #\n# Format :\
'obj [path.obj] posX,Y,Z dirX,Y,Z scaleX,Y,Z'\n"

void	write_objects(t_data *data, int fd)
{
	t_obj_attribute	*attr;
	size_t			i;

	if (data->scene.obj_list.num_elements == 0)
		return ;
	ft_putchar_fd('\n', fd);
	ft_putstr_fd(OBJECT_COMMENT, fd);
	attr = data->scene.obj_list.data;
	i = 0;
	while (i < data->scene.obj_list.num_elements)
	{
		dprintf(fd, "obj %s %.2f,%.2f,%.2f %.2f,%.2f,%.2f %.2f,%.2f,%.2f\n",
			attr[i].path, attr[i].pos.x, attr[i].pos.y, attr[i].pos.z,
			attr[i].dir.x, attr[i].dir.y, attr[i].dir.z,
			attr[i].scale.x, attr[i].scale.y, attr[i].scale.z);
		++i;
	}
}
