# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    selection.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/18 19:28:35 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/18 19:29:35 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SELECTION_DIR		= $(LOGIC_DIR)/selection

# Source files
SELECTION_SRCS		= display_selection_zone.c \
					  selection_handling.c \
					  selection_logic.c \
					  selection_scene_entries.c \
					  selection_utils.c
SRCS		+= $(addprefix $(SELECTION_DIR)/, $(SELECTION_SRCS))

# VPATH
vpath %.c $(SELECTION_DIR)
