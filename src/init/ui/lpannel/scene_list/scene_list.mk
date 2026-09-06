# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    scene_list.mk                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/18 19:14:05 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/18 20:35:17 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SCENE_LIST_DIR			= $(LPANNEL_DIR)/scene_list

# Source files
SCENE_LIST_SRCS		= init_scene_list.c \
					  populate_scene_list.c \
					  add_scene_entry.c \
					  add_cam_entry.c \
					  add_light_entry.c \
					  add_obj_entry.c \
					  select_entry.c
SRCS				+= $(addprefix $(SCENE_LIST_DIR)/, $(SCENE_LIST_SRCS))

# VPATH
vpath %.c $(SCENE_LIST_DIR)
