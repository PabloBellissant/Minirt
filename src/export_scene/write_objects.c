/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:48:39 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/20 14:25:47 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define OBJECT_COMMENT "# Custom .obj #\n# Format :\
'obj [path.obj] posX,Y,Z dirX,Y,Z scaleX,Y,Z'\n"

void	write_objects(t_data *data, int fd)
{
	t_mesh		*mesh;
	size_t		i;

	ft_putchar_fd('\n', fd);
	ft_putstr_fd(OBJECT_COMMENT, fd);
	mesh = data->scene.mesh.data;
	i = 0;
	while (i < data->scene.mesh.num_elements)
	{
		dprintf(fd, "obj %s %.2f,%.2f,%.2f %.2f,%.2f,%.2f %.2f,%.2f,%.2f\n",
			mesh[i].path, mesh[i].pos.x, mesh[i].pos.y, mesh[i].pos.z,
			mesh[i].rot.x, mesh[i].rot.y, mesh[i].rot.z,
			mesh[i].scale.x, mesh[i].scale.y, mesh[i].scale.z);
		++i;
	}
}
