# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    parsing.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:54:33 by jaubry--          #+#    #+#              #
#    Updated: 2025/07/22 21:48:51 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
PARSING_DIR		= $(SRCDIR)/parsing
OBJ_PARSER_DIR	= $(PARSING_DIR)/obj_parser
MAP_PARSER_DIR	= $(PARSING_DIR)/map

# Source files
OBJ_PARSER_SRCS	= obj_parser.c
MAP_PARSER_SRCS	= parse_map.c
SRCS			+= $(addprefix $(OBJ_PARSER_DIR)/, $(OBJ_PARSER_SRCS)) \
				   $(addprefix $(MAP_PARSER_DIR)/, $(MAP_PARSER_SRCS))

PARSING_MKS		= rt_parser/rt_parser.mk \
				  glb_parser/glb_parser.mk \
				  json_parser/json_parser.mk

include $(addprefix $(PARSING_DIR)/, $(PARSING_MKS))

# VPATH
vpath %.c $(OBJ_PARSER_DIR) $(MAP_PARSER_DIR)
