/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_xcerrcal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 21:37:36 by jaubry--          #+#    #+#             */
/*   Updated: 2025/10/13 18:45:46 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_XCERRCAL_H
# define RT_XCERRCAL_H

# define RT_ID 5

typedef enum e_rt_err
{
	RT_E_ARGS = 1,
	RT_E_GRAPHICS,
	RT_E_PARSING,
	RT_ERRS_NUM
}	t_rt_err;

#define RT_E_MSG_ARGS "Wrong argument numbers, expected 1 argument in format: \"%s <file.rt>\", got %d"
#define RT_E_MSG_GRAPHICS "Initialize of graphics component failed"
#define RT_E_MSG_PARSING "Failed to correctly parse %s file"

void	register_rt_errors(void);

#endif//RT_XCERRCAL_H
