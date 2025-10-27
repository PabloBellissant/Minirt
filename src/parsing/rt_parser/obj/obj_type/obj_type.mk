# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    type.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:41:28 by pabellis          #+#    #+#              #
#    Updated: 2025/08/04 23:24:24 by pabellis         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# Directories
OBJ_TYPE_DIR	= $(OBJ_FILE_DIR)/obj_type

# Source files
OBJ_TYPE_SRCS	= parse_vertex.c \
				  parse_normal.c \
				  parse_uv.c \
				  parse_face.c \
				  parse_mtllib.c \
				  apply_mtl.c

SRCS		+= $(addprefix $(OBJ_TYPE_DIR)/, $(OBJ_TYPE_SRCS))

# VPATH
vpath %.c $(OBJ_TYPE_DIR)
