# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    rt_parser.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 19:25:14 by jaubry--          #+#    #+#              #
#    Updated: 2025/07/22 21:55:38 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
RT_PARSER_DIR	= $(PARSING_DIR)/rt_parser
RT_TYPE_DIR		= $(RT_PARSER_DIR)/type

# Source files
RT_PARSER_SRCS	= check_double.c \
				  get_type.c \
				  parse_line.c \
				  rt_parser.c \
				  get_texture.c \
				  parse_obj_file.c
RT_TYPE_SRCS	= ambient.c \
				  camera.c \
				  light.c \
				  plane.c \
				  sphere.c \
				  obj.c \
				  mtl.c \
				  sky.c \
				  create_object.c \
				  create_texture.c

SRCS			+= $(addprefix $(RT_PARSER_DIR)/, $(RT_PARSER_SRCS)) \
				   $(addprefix $(RT_TYPE_DIR)/, $(RT_TYPE_SRCS))

RT_PARSER_MKS		= mtl/mtl.mk \
					  obj/obj.mk
include $(addprefix $(RT_PARSER_DIR)/, $(RT_PARSER_MKS))

# VPATH
vpath %.c $(RT_PARSER_DIR) $(RT_TYPE_DIR)
