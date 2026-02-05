/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:46:29 by pabellis          #+#    #+#             */
/*   Updated: 2026/02/05 00:46:29 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define HEADER "# Minirt '.rt' file.\n\n"
#define CAMERA_COMMENT "# Camera #\n# Format : 'C posX,Y,Z dirX,Y,Z fov'\n"
#define AMBIENT_COMMENT "# Ambient #\n# Format : 'A intensity R,G,B'\n"
#define SKYBOX_COMMENT "# Skybox #\n# Format : 'sky [path.ppm]'\n"

void	write_base(t_data *data, int fd)
{
	t_scene		*scene;
	t_camera	*cam;
	t_rgb_int	ambient;
	t_vec3		rot;
	t_texture	*tex;

	ft_putstr_fd(HEADER, fd);
	ft_putstr_fd(CAMERA_COMMENT, fd);
	scene = &data->scene;
	cam = &scene->camera;
	rot = vec3_div_scalar(cam->rot, M_PI);
	dprintf(fd, "C %.2f,%.2f,%.2f %.2f,%.2f,%.2f %d\n", cam->pos.x, cam->pos.y,
		cam->pos.z, rot.x, rot.y, rot.z, cam->fov);
	ft_putchar_fd('\n', fd);
	ft_putstr_fd(AMBIENT_COMMENT, fd);
	ambient = rgb_ftoi(scene->ambient);
	dprintf(fd, "A 1 %d,%d,%d\n\n",
		ambient.r, ambient.g, ambient.b);
	tex = data->scene.texture.data;
	ft_putchar_fd('\n', fd);
	if (tex[scene->skybox_tex].name != NULL)
	{
		ft_putstr_fd(SKYBOX_COMMENT, fd);
		dprintf(fd, "sky %s\n", tex[scene->skybox_tex].name);
	}
}
