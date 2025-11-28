# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ppm_parser.mk                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:41:28 by pabellis          #+#    #+#              #
#    Updated: 2025/08/04 23:24:24 by pabellis         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# Directories
PPM_PARSER_DIR	= $(PARSING_DIR)/ppm_parser

# Source files
PPM_PARSER_SRCS	= binary_rgb_parser.c \
				  binary_parser.c \
				  skip_comment.c \
				  check_header.c

SRCS		+= $(addprefix $(PPM_PARSER_DIR)/, $(PPM_PARSER_SRCS))

# VPATH
vpath %.c $(PPM_PARSER_DIR)
