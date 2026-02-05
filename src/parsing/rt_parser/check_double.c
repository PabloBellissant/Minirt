/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 03:26:31 by pabellis          #+#    #+#             */
/*   Updated: 2025/08/13 14:49:46 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "xcerrcal.h"
#include "rt_xcerrcal.h"

#define FORBIDDEN_COUNT 2

int	check_double(t_object_type type)
{
	static const t_object_type	forbidden_double[] = {AMBIENT, CAMERA};
	static int					elem_count[OBJ_ENUM_SIZE];
	static const char			*type_name[] = {"Undefined",
		"Ambient", "Camera", "Light", "Sphere", "Plane"};
	int							i;

	i = 0;
	while (i < FORBIDDEN_COUNT)
	{
		if (type == forbidden_double[i])
		{
			if (elem_count[type] == 1)
			{
				register_complex_err_msg(RT_E_MSG_FB_DOUBLE, type_name[type]);
				return (error(pack_err(RT_ID, RT_E_FB_DOUBLE), FL, LN, FC));
			}
			elem_count[type] = 1;
			return (0);
		}
		++i;
	}
	return (0);
}
