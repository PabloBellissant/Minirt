# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    parsing.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/08 09:10:09 by jaubry--          #+#    #+#              #
#    Updated: 2025/04/01 14:02:21 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
PARSE_DIR	= $(SRCDIR)/parsing

# Source files
PARSE_SRCS	= is_in.c has_in.c \
			  count_tokens.c \
			  ft_strtok.c \
			  ft_isalnum.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_isspace.c \
			  ft_isalpha.c

SRCS		+= $(addprefix $(PARSE_DIR)/, $(PARSE_SRCS))

# VPATH
vpath %.c $(PARSE_DIR)
