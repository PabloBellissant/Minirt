/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:47:39 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/05 00:47:39 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define LIGHT_COMMENT "# Light #\n# Format : 'L posX,Y,Z intensity R,G,B'\n"

void	write_lights(t_data *data, int fd)
{
	size_t		i;
	t_object	*obj;
	t_rgb_int	rgb;

	if (data->scene.light.num_elements == 0)
		return ;
	ft_putchar_fd('\n', fd);
	ft_putstr_fd(LIGHT_COMMENT, fd);
	obj = data->scene.light.data;
	i = 0;
	while (i < data->scene.light.num_elements)
	{
		rgb = rgb_ftoi(obj[i].light.rgb);
		dprintf(fd, "L %.2f,%.2f,%.2f 1 %d,%d,%d\n",
			obj[i].light.pos.x, obj[i].light.pos.y, obj[i].light.pos.z,
			rgb.r, rgb.g, rgb.b);
		++i;
	}
}
