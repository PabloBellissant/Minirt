# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    parsing.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:54:33 by jaubry--          #+#    #+#              #
#    Updated: 2025/12/09 15:43:16 by pabellis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
PARSING_DIR		= $(SRCDIR)/parsing

# Source files
PARSING_SRCS	= parse_scene.c \
				  fill_by_type.c \
				  fill_gpu_data.c
SRCS			+= $(addprefix $(PARSING_DIR)/, $(PARSING_SRCS))

PARSING_MKS		= rt_parser/rt_parser.mk
include $(addprefix $(PARSING_DIR)/, $(PARSING_MKS))

# VPATH
vpath %.c $(PARSING_DIR)
