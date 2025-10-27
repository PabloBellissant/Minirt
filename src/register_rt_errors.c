/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_rt_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:33:07 by jaubry--          #+#    #+#             */
/*   Updated: 2025/10/13 18:45:04 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_xcerrcal.h"
#include "rt_xcerrcal.h"
#include "xcerrcal.h"
#include "rt_xcerrcal.h"

void	register_rt_errors(void)
{
	const char	*err_msgs[] =
	{
		RT_E_MSG_ARGC,
		RT_E_MSG_GRAPHICS,
		RT_E_MSG_PARSING,
		RT_E_MSG_ARGS,
		RT_E_MSG_AMBIENT,
		RT_E_MSG_CAMERA,
		RT_E_MSG_CYLINDER,
		RT_E_MSG_LIGHT,
		RT_E_MSG_OBJ,
		RT_E_MSG_PLANE,
		RT_E_MSG_SKY,
		RT_E_MSG_SPHERE,
		RT_E_MSG_TEX,
		RT_E_MSG_MAT,
		RT_E_MSG_OBJ_FAIL,
		RT_E_MSG_NO_TEX,
		RT_E_MSG_NO_PARSER,
		RT_E_MSG_FB_DOUBLE,
		RT_E_MSG_FB_NO,
	};
	bulk_register_error(RT_ERRS_NUM - 1, RT_ID, (const char **)err_msgs);
}
