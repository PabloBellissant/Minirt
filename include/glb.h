/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glb.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 03:59:01 by pabellis          #+#    #+#             */
/*   Updated: 2025/05/16 03:59:06 by pabellis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLB_H
# define GLB_H

# include "struct.h"
# include "json.h"

t_obj		*glb_parser(char *str);
t_obj		get_object_data(int elem, char *str);
char		*get_scene_name(t_json *json);
int			get_object_count(t_json *json);
int			get_vertex_count(t_json *json, int accessors_id);
t_obj		*parse_objects(t_json *json, void *binary);
int			get_mesh_id(t_json *json, int object_id);
int			get_pos_accessors(t_json *json, int object_id);
t_vertex	*get_vertex(t_json *json, void *binary, int id);

#endif
