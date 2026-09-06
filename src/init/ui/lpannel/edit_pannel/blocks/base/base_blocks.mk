# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    base_blocks.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/18 19:26:43 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/19 11:03:08 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
BASE_BLOCKS_DIR		= $(BLOCKS_DIR)/base

# Source files
BASE_BLOCKS_SRCS	= add_edit_block.c \
					  add_block_title.c \
					  add_form_block.c \
					  add_inner_edit.c \
					  add_edit_pannel_title.c
SRCS				+= $(addprefix $(BASE_BLOCKS_DIR)/, $(BASE_BLOCKS_SRCS))

# VPATH
vpath %.c $(BASE_BLOCKS_DIR)
