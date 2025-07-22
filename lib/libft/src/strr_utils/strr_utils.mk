# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    strr_utils.mk                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/08 09:14:34 by jaubry--          #+#    #+#              #
#    Updated: 2025/04/01 14:52:41 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
STRR_DIR	= $(SRCDIR)/strr_utils

# Source files
STRR_SRCS	= ft_split.c split_by_char.c \
			  strr_utils.c
SRCS		+= $(addprefix $(STRR_DIR)/, $(STRR_SRCS))

# VPATH
vpath %.c $(STRR_DIR)
