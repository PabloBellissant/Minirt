# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mtl.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:41:28 by pabellis          #+#    #+#              #
#    Updated: 2025/08/04 23:24:24 by pabellis         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# Directories
OBJ_FILE_DIR	= $(RT_PARSER_DIR)/obj

# Source files
OBJ_FILE_SRCS	= parse_obj_type.c \
				  get_obj_type.c

SRCS		+= $(addprefix $(OBJ_FILE_DIR)/, $(OBJ_FILE_SRCS))

OBJ_FILE_MKS		= obj_type/obj_type.mk
include $(addprefix $(OBJ_FILE_DIR)/, $(OBJ_FILE_MKS))

# VPATH
vpath %.c $(OBJ_FILE_DIR)
