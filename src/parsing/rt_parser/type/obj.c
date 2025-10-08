/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 02:12:53 by pabellis          #+#    #+#             */
/*   Updated: 2025/10/02 02:12:57 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "calc.h"
#include "vectors.h"

#define OBJ_FORMAT " *obj  *%s  *%f *, *%f *, *%f *\n"

int	parse_obj_file(int fd, t_scene *scene, t_vec3 *pos);

int	obj(const char *line, int line_num, t_scene *scene)
{
	char	*obj_directory;
	t_vec3	pos;

	if (ft_scan(line_num, OBJ_FORMAT, line, &obj_directory, &pos.x, &pos.y, &pos.z))
		return (-1);
	parse_obj_file(open(obj_directory, O_RDONLY), scene, &pos);
	return (0);
}
