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
#include "rt_xcerrcal.h"

#define OBJ_FORMAT " *obj  *%s  *%f *, *%f *, *%f  *%f *, *%f *, *%f  *%f *, *%f *, *%f *\n"

int	parse_obj_file(int fd, t_scene *scene, t_pos_attribute *attr);

int	obj(const char *line, int line_num, t_scene *scene)
{
	char			*obj_directory;
	t_pos_attribute	attr;

	obj_directory = NULL;
	if (ft_scan(line_num, OBJ_FORMAT, line, &obj_directory,
		&attr.pos.x, &attr.pos.y, &attr.pos.z,
		&attr.dir.x, &attr.dir.y, &attr.dir.z,
		&attr.scale.x, &attr.scale.y, &attr.scale.z))
	{
		free(obj_directory);
		return (error(pack_err(RT_ID, RT_E_OBJ), FL, LN, FC));
	}
	if (ft_strlen(obj_directory) <= 4
		|| ft_strrncmp(".obj", obj_directory, 4) != 0)
	{
		free(obj_directory);
		return (error(pack_err(RT_ID, RT_E_OBJ), FL, LN, FC));
	}
	register_complex_err_msg(RT_E_MSG_OBJ_FAIL, obj_directory);
	if (parse_obj_file(open(obj_directory, O_RDONLY), scene, &attr) == -1)
	{
		free(obj_directory);
		return (error(pack_err(RT_ID, RT_E_OBJ_FAIL), FL, LN, FC));
	}
	free(obj_directory);
	return (0);
}

