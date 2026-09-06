/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_edit.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:54:37 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/18 20:17:13 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_EDIT_H
# define OBJ_EDIT_H

t_hbranch	*rebuild_obj_edit(t_data *data, t_hbranch *lpannel_edit);

bool		is_tex_editable(t_texture *tex);

t_hbranch	*add_obj_title(t_hbranch *obj_edit, int *y_size, t_object *obj);

#endif//OBJ_EDIT_H
