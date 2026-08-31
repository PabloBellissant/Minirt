/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_list.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:37:39 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 18:03:49 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_LIST_H
# define SCENE_LIST_H

# define ENTRY_HEIGHT 24
# define MAX_SCENE_ENTRIES 50
# define MAX_SCENE_ENTRIES_MSG "Arrived at max scene entries size %d"
# define MAX_SCENE_LOG "WARNING: maxed out scene entries, entries will no \
	longer be displayed after %dth entry\n"

typedef struct s_scene_entry
{
	t_object	*obj;
	t_hbranch	*entry;
}				t_scene_entry;

int			populate_scene_list(t_data *data, t_hbranch *scene_list,
				size_t *num_entries);
t_hbranch	*add_scene_entry(t_hbranch *scene_list, char *name,
				t_object *obj, t_data *data);

#endif//SCENE_LIST_H
