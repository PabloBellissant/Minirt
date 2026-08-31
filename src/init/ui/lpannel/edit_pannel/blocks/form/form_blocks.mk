# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    form_blocks.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/18 19:25:18 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/18 19:26:04 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
FORM_BLOCKS_DIR		= $(BLOCKS_DIR)/form

# Source files
FORM_BLOCKS_SRCS		= add_float_edit.c \
						  add_vec3_edit.c
SRCS					+= $(addprefix $(FORM_BLOCKS_DIR)/, $(FORM_BLOCKS_SRCS))

# VPATH
vpath %.c $(FORM_BLOCKS_DIR)
