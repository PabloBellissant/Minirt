# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    colorpicker_blocks.mk                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/18 19:25:50 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/18 19:26:35 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
COLORPICKER_BLOCKS_DIR		= $(BLOCKS_DIR)/colorpicker

# Source files
COLORPICKER_BLOCKS_SRCS		= add_color_edit.c \
							  add_texture_edit.c
SRCS						+= $(addprefix $(COLORPICKER_BLOCKS_DIR)/, $(COLORPICKER_BLOCKS_SRCS))

# VPATH
vpath %.c $(COLORPICKER_BLOCKS_DIR)
