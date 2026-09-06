# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    on_display.mk                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/18 19:07:08 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/18 19:10:46 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
ON_DISPLAY_DIR		= $(UI_DIR)/on_display

# Source files
ON_DISPLAY_SRCS		= init_ondisplay.c \
					  add_render_switch.c
SRCS				+= $(addprefix $(ON_DISPLAY_DIR)/, $(ON_DISPLAY_SRCS))

ON_DISPLAY_MKS		= fps/fps.mk \
					  info_display/info_display.mk
include $(addprefix $(ON_DISPLAY_DIR)/, $(ON_DISPLAY_MKS))

# VPATH
vpath %.c $(ON_DISPLAY_DIR)
