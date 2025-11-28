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
MTL_DIR	= $(RT_PARSER_DIR)/mtl

# Source files
MTL_SRCS	= create_mat.c \
			  parse_mtl_file.c \
			  get_mtl_type.c \
			  parse_mtl_type.c \
			  get_mat.c \
			  create_default_mat.c \
			  create_null_texture.c \
			  create_null_nmap.c \
			  create_null_roughness.c \
			  create_null_ambient.c \
			  create_null_opacity.c

SRCS		+= $(addprefix $(MTL_DIR)/, $(MTL_SRCS))

MTL_MKS		= type/type.mk
include $(addprefix $(MTL_DIR)/, $(MTL_MKS))

# VPATH
vpath %.c $(MTL_DIR)
