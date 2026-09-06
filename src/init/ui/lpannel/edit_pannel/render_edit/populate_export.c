/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:25:54 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/19 20:30:24 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline int	add_export_button_label(t_hbranch *button, char *label)
{
	t_hbranch	*textbox;

	textbox = add_textbox(button, (t_text){.font_size = 2,
			.fg = (t_rgba_int){.rgba = WHITE}}, CENTER_ALIGN, NO_WRAPPING);
	if (!textbox)
		return (1);
	textbox->pos = button->pos;
	textbox->size = button->size;
	textbox->anchor = RT;
	textbox->textbox.vert_align = MIDDLE_ALIGN;
	ft_strlcpy(textbox->textbox.content, label, MAX_CHARS);
	return (0);
}

void	export_scene(t_data *data, t_mlx *mlx);
void	schedule_render_task(t_hbranch *v, t_data *data, t_mlx *mlx);

static inline void	export_scene_action(t_hbranch *v, t_data *data,
						t_mlx *mlx)
{
	(void)v;
	if (DEBUG)
		printf("EXPOR START\n");
	export_scene(data, mlx);
	if (DEBUG)
		printf("EXPORT STOP\n");
}

static inline int	add_export_button(t_block_util bl,
						void (*action)(t_hbranch *, t_data *, t_mlx *))
{
	t_hbranch	*button;

	button = add_button(bl.comp, (t_radius){.style = FULL_PX, .full = 9},
			(t_border){.style = SOLID, .size = 1,
			.color = bl.comp->head->style.border});
	if (!button)
		return (1);
	button->anchor = RT;
	button->pos = vec2i(bl.comp->pos.x + bl.comp->size.x, *bl.y_size);
	button->size = vec2i(160, 36);
	button->box.color = bl.comp->head->style.input;
	button->button.action2 = (t_action2 *)action;
	button->button.args2[0] = bl.data;
	button->button.args2[1] = bl.data->mlx;
	if (add_export_button_label(button, bl.name) != 0)
		return (1);
	*bl.y_size += button->box.size.y + INBLOCK_PADDING;
	return (0);
}

int	populate_export_buttons(t_data *data, t_hbranch *render_edit, int *y_size)
{
	t_hbranch		*block_title;
	t_block_util	bl;

	bl = (t_block_util){.comp = add_edit_block(render_edit, y_size),
		.y_size = y_size, .name = "Export", .data = data};
	if (!bl.comp)
		return (1);
	block_title = add_block_title(bl);
	if (!block_title)
		return (1);
	bl.name = "EXPORT SCENE";
	if (add_export_button(bl, export_scene_action) != 0)
		return (1);
	bl.name = "EXPORT IMAGE";
	if (add_export_button(bl, schedule_render_task) != 0)
		return (1);
	bl.comp->size.y = *y_size - bl.comp->size.y;
	return (0);
}
