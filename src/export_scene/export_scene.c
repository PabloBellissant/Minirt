/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 17:20:56 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/12 00:52:26 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "minirt.h"
#include "export.h"

void	export_scene(t_data *data, t_mlx *mlx)
{
	int	fd;

	(void) mlx;
	fd = open("exported.rt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
		return ;
	write_base(data, fd);
	write_materials(data, fd);
	write_lights(data, fd);
	write_primitives(data, fd);
	write_objects(data, fd);
	close(fd);
}
