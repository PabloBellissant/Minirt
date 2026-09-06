# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ui_logic.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/18 19:27:36 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/19 19:14:54 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
LOGIC_DIR		= $(UI_DIR)/logic

# Source files
LOGIC_SRCS		= reload_mat_utils.c \
				  reload_scene_utils.c \
				  get_obj_label.c
SRCS			+= $(addprefix $(LOGIC_DIR)/, $(LOGIC_SRCS))

LOGIC_MKS		= selection/selection.mk
include $(addprefix $(LOGIC_DIR)/, $(LOGIC_MKS))

# VPATH
vpath %.c $(LOGIC_DIR)
