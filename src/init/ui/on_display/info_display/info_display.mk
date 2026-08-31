# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    info_display.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/18 19:08:47 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/18 19:10:37 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
INFO_DISPLAY_DIR	= $(ON_DISPLAY_DIR)/info_display

# Source files
INFO_DISPLAY_SRCS	= add_info_display.c \
					  update_info_display.c \
					  update_info_display_global.c \
					  update_info_display_selected.c
SRCS				+= $(addprefix $(INFO_DISPLAY_DIR)/, $(INFO_DISPLAY_SRCS))

# VPATH
vpath %.c $(INFO_DISPLAY_DIR)
