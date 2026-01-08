/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:00:19 by pabellis          #+#    #+#             */
/*   Updated: 2026/01/02 22:00:19 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minirt.h"
#include "parsing.h"
#include "vec3_scalar.h"
#include "vec3_special2.h"
#include "calc.h"
#include <fcntl.h>

#define HEADER "# Minirt '.rt' file.\n\n"
#define CAMERA_COMMENT "# Camera #\n# Format : 'C posX,Y,Z dirX,Y,Z fov'\n"
#define AMBIENT_COMMENT "# Ambient #\n# Format : 'A intensity R,G,B'\n"
#define SKYBOX_COMMENT "# Skybox #\n# Format : 'sky [path.ppm]'\n"
#define LIGHT_COMMENT "# Light #\n# Format : 'L posX,Y,Z intensity R,G,B'\n"
#define MATERIALS_COMMENT "# Materials #\n# Format : 'mtl [path.mtl]'\n"
#define PRIMITIVE_COMMENT "# Primitive #\n#  - Sphere format : 'sp posX,Y,Z diameter material_name'\n#  - Plane format : 'pl posX,Y,Z normX,Y,Z material_name scaling'\n"
#define OBJECT_COMMENT "# Custom .obj #\n# Format : 'obj [path.obj] posX,Y,Z dirX,Y,Z scaleX,Y,Z'\n"

static void	write_base(t_data *data, int fd);
static void	write_materials(t_data *data, int fd);
static void	write_lights(t_data *data, int fd);
static void	write_primitives(t_data *data, int fd);
static void	write_objects(t_data *data, int fd);

void	export_scene(t_data *data, t_mlx *mlx)
{
	(void) mlx;
	int	fd;

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

static void	write_base(t_data *data, int fd)
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
	dprintf(fd, "C %.2f,%.2f,%.2f %.2f,%.2f,%.2f %d\n", \
		 cam->pos.x, cam->pos.y, cam->pos.z, \
		 rot.x, rot.y, rot.z, cam->fov);
	ft_putchar_fd('\n', fd);
	ft_putstr_fd(AMBIENT_COMMENT, fd);
	ambient = rgb_ftoi(scene->ambient);
	dprintf(fd, "A 1 %d,%d,%d\n\n", \
		 ambient.r, ambient.g, ambient.b);
	tex = data->scene.texture.data;
	ft_putchar_fd('\n', fd);
	ft_putstr_fd(SKYBOX_COMMENT, fd);
	dprintf(fd, "sky %s\n", tex[scene->skybox_tex].name);
}

static void	write_materials(t_data *data, int fd)
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

static void	write_lights(t_data *data, int fd)
{
	size_t		i;
	t_object	*obj;
	t_rgb_int	rgb;

	if (data->scene.lights.num_elements == 0)
		return ;
	ft_putchar_fd('\n', fd);
	ft_putstr_fd(LIGHT_COMMENT, fd);
	obj = data->scene.lights.data;
	i = 0;
	while (i < data->scene.lights.num_elements)
	{
		rgb = rgb_ftoi(obj[i].light.rgb);
		dprintf(fd, "L %.2f,%.2f,%.2f 1 %d,%d,%d\n", \
			obj[i].light.pos.x, obj[i].light.pos.y, obj[i].light.pos.z, \
			rgb.r, rgb.g, rgb.b);
		++i;
	}
}
static void	write_primitives(t_data *data, int fd)
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
			dprintf(fd, "sp %.2f,%.2f,%.2f %.2f 0,0,0 %s\n", \
			obj[i].sphere.pos.x, obj[i].sphere.pos.y, obj[i].sphere.pos.z, \
			obj[i].sphere.diameter, obj[i].name);
		else if (obj[i].type == PLANE)
			dprintf(fd, "pl %.2f,%.2f,%.2f %.2f,%.2f,%.2f 0,0,0 %s %.2f\n", \
			obj[i].plane.pos.x, obj[i].plane.pos.y, obj[i].plane.pos.z, \
		   	obj[i].plane.normal.x, obj[i].plane.normal.y, \
			obj[i].plane.normal.z, obj[i].name, obj[i].plane.texture_scaling);
		++i;
	}
}

static void	write_objects(t_data *data, int fd)
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
		dprintf(fd, "obj %s %.2f,%.2f,%.2f %.2f,%.2f,%.2f %.2f,%.2f,%.2f", \
			attr[i].path, attr[i].pos.x, attr[i].pos.y, attr[i].pos.z, \
			attr[i].dir.x, attr[i].dir.y, attr[i].dir.z, \
			attr[i].scale.x, attr[i].scale.y, attr[i].scale.z);
		++i;
	}
}

