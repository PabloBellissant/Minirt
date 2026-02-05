/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_primitives.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:48:06 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/05 00:48:06 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define PRIMITIVE_COMMENT "# Primitive #\n#  - Sphere format : \
'sp posX,Y,Z diameter material_name'\n#  - Plane format : \
'pl posX,Y,Z normX,Y,Z material_name scaling'\n"

void	write_primitives(t_data *data, int fd)
{
	size_t		i;
	t_object	*obj;

	if (data->scene.objects.num_elements == 0)
		return ;
	ft_putchar_fd('\n', fd);
	ft_putstr_fd(PRIMITIVE_COMMENT, fd);
	obj = data->scene.objects.data;
	i = 0;
	while (i < data->scene.objects.num_elements)
	{
		if (obj[i].type == SPHERE)
			dprintf(fd, "sp %.2f,%.2f,%.2f %.2f 0,0,0 %s\n",
				obj[i].sphere.pos.x, obj[i].sphere.pos.y, obj[i].sphere.pos.z,
				obj[i].sphere.diameter, obj[i].name);
		else if (obj[i].type == PLANE)
			dprintf(fd, "pl %.2f,%.2f,%.2f %.2f,%.2f,%.2f 0,0,0 %s %.2f\n",
				obj[i].plane.pos.x, obj[i].plane.pos.y, obj[i].plane.pos.z,
				obj[i].plane.normal.x, obj[i].plane.normal.y,
				obj[i].plane.normal.z, obj[i].name,
				obj[i].plane.texture_scaling);
		++i;
	}
}
