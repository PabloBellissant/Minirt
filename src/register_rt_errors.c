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

#include "xcerrcal.h"
#include "rt_xcerrcal.h"

void	register_rt_errors(void)
{
	const char	*err_msgs[] =
	{
		RT_E_MSG_ARGS,
		RT_E_MSG_GRAPHICS,
		RT_E_MSG_PARSING
	};
	bulk_register_error(RT_ERRS_NUM - 1, RT_ID, (const char **)err_msgs);
}
