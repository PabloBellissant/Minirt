# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    json_parser.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:46:19 by jaubry--          #+#    #+#              #
#    Updated: 2025/07/22 18:49:23 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
JSON_DIR	= $(PARSING_DIR)/json_parser

# Source files
JSON_SRCS	= json_parser.c \
			  recursive_parse.c \
			  extract_len.c \
			  fill_json_data.c \
			  get_end_brackets.c \
			  get_next_data.c \
			  get_json_type.c \
			  fill_array.c \
			  get_by_key_name.c \
			  fix_json_str.c
SRCS		+= $(addprefix $(JSON_DIR)/, $(JSON_SRCS))

# VPATH
vpath %.c $(JSON_DIR)
