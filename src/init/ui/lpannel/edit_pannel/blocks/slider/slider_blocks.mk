# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    slider_blocks.mk                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/18 19:23:57 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/18 19:25:10 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SLIDER_BLOCKS_DIR		= $(BLOCKS_DIR)/slider

# Source files
SLIDER_BLOCKS_SRCS		= add_grayscale_edit.c \
						  add_slider_edit.c
SRCS					+= $(addprefix $(SLIDER_BLOCKS_DIR)/, $(SLIDER_BLOCKS_SRCS))

# VPATH
vpath %.c $(SLIDER_BLOCKS_DIR)
