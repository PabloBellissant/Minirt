# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ui.mk                                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/18 19:04:55 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/18 19:10:59 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
UI_DIR		= $(INIT_DIR)/ui

# Source files
UI_SRCS		= init_ui.c \
			  populate_ui.c
SRCS		+= $(addprefix $(UI_DIR)/, $(UI_SRCS))

UI_MKS		= logic/ui_logic.mk \
			  lpannel/lpannel.mk \
			  on_display/on_display.mk

include $(addprefix $(UI_DIR)/, $(UI_MKS))

# VPATH
vpath %.c $(UI_DIR)
