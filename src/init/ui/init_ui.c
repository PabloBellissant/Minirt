/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:27:08 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 19:13:13 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline t_style	get_style(void)
{
	return (
		(t_style)
		{
			.radius = 9,
			.background = drgba_int(C_BACKGROUND),
			.foreground = drgba_int(C_FOREGROUND),
			.card = drgba_int(C_CARD),
			.primary = drgba_int(C_PRIMARY),
			.primary_fg = drgba_int(C_PRIMARY_FG),
			.secondary = drgba_int(C_SECONDARY),
			.secondary_fg = drgba_int(C_SECONDARY_FG),
			.muted = drgba_int(C_MUTED),
			.muted_fg = drgba_int(C_MUTED_FG),
			.accent = drgba_int(C_ACCENT),
			.accent_fg = drgba_int(C_ACCENT_FG),
			.destructive = drgba_int(C_DESTRUCTIVE),
			.border = drgba_int(C_BORDER),
			.input = drgba_int(C_INPUT),
			.highlight = drgba_int(C_HIGHLIGHT),
		}
	);
}

static inline int	create_body(t_data *data)
{
	data->ui.htree.body = ft_calloc(1, sizeof(t_hbranch));
	if (!data->ui.htree.body)
		return (1);
	data->ui.htree.body->type = BOX;
	data->ui.htree.body->visible = false;
	data->ui.htree.body->rendered = true;
	data->ui.htree.body->parent = NULL;
	data->ui.htree.body->head = &data->ui.htree;
	data->ui.htree.body->childs = ft_calloc(sizeof(t_vector), 1);
	if (!data->ui.htree.body->childs)
		return (1);
	data->ui.htree.body->box = (t_box)
	{
		.img = &data->mlx->img,
		.precompute = precompute_box,
		.render = (t_action *)render_box,
		.anchor = LT,
		.size = data->mlx->size,
		.pos = data->mlx->origin,
	};
	data->ui.ui_toggle = &data->ui.htree.body->rendered;
	return (0);
}

static inline void	init_ui_misc(t_data *data)
{
	vector_init(&data->ui.selection.selected, sizeof(t_object *));
	data->ui.lpannel_width = (int)((float)WIDTH / 5.f);
	data->ui.scene_height = (int)((float)HEIGHT / 4.f);
	data->ui.lpannel_switch_height = 35;
	data->ui.lpannel_edit_height = HEIGHT
		- (data->ui.scene_height + data->ui.lpannel_switch_height);
}

static inline void	debug_ui(t_htree *htree)
{
	const char	*comp_names[COLORPICKER + 1] = {"EMPTY", "BOX", "CHECKBOX",
		"TEXTBOX", "BUTTON", "BUTTON_GROUP", "FORM", "SELECT", "IMAGE",
		"SCROLLBOX", "SLIDER", "COLORPICKER"};
	size_t		i;
	t_hbranch	**br;

	i = 0;
	br = htree->refs.data;
	while (i < htree->refs.num_elements)
	{
		printf("%s-%zu\n", comp_names[br[i]->type], i);
		i++;
	}
}

int	populate_ui(t_data *data, t_hbranch *body);

int	init_ui(t_data *data)
{
	data->ui.htree = init_htree(data->mlx, get_style());
	if (create_body(data) != 0)
		return (1);
	if (init_ttf(FONT_PATH, &data->ui.htree.style.font) != 0)
		return (1);
	init_ui_misc(data);
	if (populate_ui(data, data->ui.htree.body) != 0)
		return (1);
	precompute_hierarchy(&data->ui.htree);
	if (DEBUG)
		debug_ui(&data->ui.htree);
	return (0);
}
