# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    glb_parser.mk                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:49:51 by jaubry--          #+#    #+#              #
#    Updated: 2025/07/22 19:24:47 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
GLB_DIR			= $(PARSING_DIR)/glb_parser
GLB_DATA_DIR	= $(GLB_DIR)/data

# Source files
GLB_SRCS		= glb_parser.c parse_objects.c
GLB_DATA_SRCS	= get_object_data.c \
				  get_scene_name.c \
				  get_object_count.c \
				  get_vertex_count.c \
				  get_mesh_id.c \
				  get_pos_accessors.c \
				  get_vertex.c
SRCS			+= $(addprefix $(GLB_DIR)/, $(GLB_SRCS)) \
				   $(addprefix $(GLB_DATA_DIR)/, $(GLB_DATA_SRCS))

# VPATH
vpath %.c $(GLB_DIR) $(GLB_DATA_DIR)
