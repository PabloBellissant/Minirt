/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 02:12:53 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/14 09:37:23 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "calc.h"
#include "parsing.h"
#include "rt_xcerrcal.h"

#define OBJ_FORMAT " *obj  *%s  *%f *, *%f *, *%f  *%f *, *%f *, *%f  *%f *, *%f *, *%f *\n"

int						parse_obj_file(int fd, t_scene *scene, t_obj_attribute *attr);
static t_obj_attribute	*create_raw_attribute(t_scene *scene);

int	obj(const char *line, int line_num, t_scene *scene)
{
	t_obj_attribute	*attr;

	attr = create_raw_attribute(scene);
	if (ft_scan(line_num, OBJ_FORMAT, line, &attr->path,
		&attr->pos.x, &attr->pos.y, &attr->pos.z,
		&attr->dir.x, &attr->dir.y, &attr->dir.z,
		&attr->scale.x, &attr->scale.y, &attr->scale.z))
	{
		free(attr->path);
		return (error(pack_err(RT_ID, RT_E_OBJ), FL, LN, FC));
	}
	if (ft_strlen(attr->path) <= 4
		|| ft_strrncmp(".obj", attr->path, 4) != 0)
	{
		return (error(pack_err(RT_ID, RT_E_OBJ), FL, LN, FC));
	}
	register_complex_err_msg(RT_E_MSG_OBJ_FAIL, attr->path);
	if (parse_obj_file(open(attr->path, O_RDONLY), scene, attr) == -1)
		return (error(pack_err(RT_ID, RT_E_OBJ_FAIL), FL, LN, FC));
	return (0);
}

static t_obj_attribute	*create_raw_attribute(t_scene *scene)
{
	t_obj_attribute	attr;

	ft_bzero(&attr, sizeof(t_obj_attribute));
	if (scene->obj_list.num_elements == 0)
		vector_init(&scene->obj_list, sizeof(t_obj_attribute));
	if (vector_add(&scene->obj_list, &attr, 1) == -1)
		return (NULL);
	return (get_last_vector_value(&scene->obj_list));
}

