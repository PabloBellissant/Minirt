/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_materials.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:47:15 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/12 00:52:47 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define MATERIALS_COMMENT "# Materials #\n# Format : 'mtl [path.mtl]'\n"

void	write_materials(t_data *data, int fd)
{
	size_t		i;
	char		**mtl_path;

	if (data->scene.mtl_list.num_elements == 0)
		return ;
	ft_putchar_fd('\n', fd);
	ft_putstr_fd(MATERIALS_COMMENT, fd);
	mtl_path = data->scene.mtl_list.data;
	i = 0;
	while (i < data->scene.mtl_list.num_elements)
	{
		dprintf(fd, "mtl %s\n", mtl_path[i]);
		++i;
	}
}
