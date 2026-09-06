/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_pannel.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:40:44 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/20 14:19:20 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDIT_PANNEL_H
# define EDIT_PANNEL_H

# define BLOCK_HEIGHT 35
# define BLOCK_PADDING 20
# define INBLOCK_PADDING 10

typedef enum e_edit_mode
{
	OBJ_EDIT_MODE = 0,
	RENDER_EDIT_MODE
}	t_edit_mode;

void		destroy_edit_pannel(t_data *data);
t_hbranch	*rebuild_inner_edit(t_hbranch *v, t_data *data,
				t_hbranch *edit_pannel);

#endif//EDIT_PANNEL_H
