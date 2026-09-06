/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 03:01:18 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 18:03:26 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include "mlxui.h"
# include "font_renderer.h"
# include "object.h"

# include "on_display.h"
# include "scene_list.h"

# include "blocks.h"
# include "edit_pannel.h"
# include "obj_edit.h"

# include "reload_utils.h"
# include "selection.h"
# include "ui_utils.h"

# define SELECT_COLOR	0xff8c00
# define FSELECT_COLOR	0xe86100 // first selected color

# define C_BACKGROUND	0xff1c151e
# define C_FOREGROUND	0xFFFDFDFD
# define C_CARD			0xff211b23
# define C_PRIMARY		0xFFF7A83B
# define C_PRIMARY_FG	0xFFFCF2E8
# define C_SECONDARY	0xFF2F2C37
# define C_SECONDARY_FG	0xFFFDFDFD
# define C_MUTED		0xFF2F2C37
# define C_MUTED_FG		0xFFB2B5D6
# define C_ACCENT		0xFF2F2C37
# define C_ACCENT_FG	0xFFFDFDFD
# define C_DESTRUCTIVE	0xFFE25A2B
# define C_BORDER		0xff403743
# define C_INPUT		0xff2e2730
# define C_HIGHLIGHT	0x239c949f

# define FONT_PATH "assets/fonts/JetBrainsMono-ExtraLight.ttf"

typedef struct s_ui
{
	t_htree			htree;
	t_selection		selection;
	int				lpannel_width;
	int				scene_height;
	int				lpannel_switch_height;
	int				lpannel_edit_height;
	bool			export_render_task;

	t_hbranch		*edit_pannel;
	union
	{
		t_hbranch	*inner_edit;
		t_hbranch	*obj_edit;
		t_hbranch	*bvh_edit;
		t_hbranch	*render_edit;
	};
	int				*edit_mode;

	t_hbranch		*lpannel_switch;
	t_hbranch		*render_switch;

	char			*fps_buffer;
	char			*info_buffer;

	t_scene_entry	scene_entries[MAX_SCENE_ENTRIES];

	bool			*lpannel_toggle;
	bool			*ui_toggle;
}					t_ui;

int	init_ui(t_data *data);

#endif//UI_H
