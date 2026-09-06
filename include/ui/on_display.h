/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_display.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 18:43:16 by jaubry--          #+#    #+#             */
/*   Updated: 2026/02/18 18:46:16 by jaubry--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ON_DISPLAY_H
# define ON_DISPLAY_H

# define RENDER_MODES 4
# define WIREFRAME_LOGO_PATH	"assets/ui_logo/wireframe-logo.pam"
# define PHONG_LOGO_PATH		"assets/ui_logo/phong-logo.pam"
# define PBR_LOGO_PATH			"assets/ui_logo/pbr-logo.pam"
# define MONTE_CARLO_LOGO_PATH	"assets/ui_logo/monte-carlo-logo.pam"

# define INFO_DISPLAY_X 50
# define INFO_DISPLAY_Y 240
# define INFO_DISPLAY_OPACITY 15

void	update_info_display(t_data *data);

void	update_fps(t_data *data);
void	fps_counter(int frame);

#endif//ON_DISPLAY_H
