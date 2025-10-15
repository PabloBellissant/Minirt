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
#include "vectors.h"
#include "rt_xcerrcal.h"

#define OBJ_FORMAT " *obj  *%s  *%f *, *%f *, *%f *\n"

int	parse_obj_file(int fd, t_scene *scene, t_vec3 *pos);

int	obj(const char *line, int line_num, t_scene *scene)
{
	char	*obj_directory;
	t_vec3	pos;

	if (ft_scan(line_num, OBJ_FORMAT, line, &obj_directory, &pos.x,
			&pos.y, &pos.z))
	{
		return (error(pack_err(RT_ID, RT_E_OBJ), FL, LN, FC));
	}
	if (parse_obj_file(open(obj_directory, O_RDONLY), scene, &pos) == -1)
	{
		register_complex_err_msg(RT_E_MSG_OBJ_FAIL, obj_directory);
		return (error(pack_err(RT_ID, RT_E_OBJ_FAIL), FL, LN, FC));
	}
	return (0);
}
