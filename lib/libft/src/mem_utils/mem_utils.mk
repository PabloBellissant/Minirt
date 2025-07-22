# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mem_utils.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/08 09:14:34 by jaubry--          #+#    #+#              #
#    Updated: 2025/07/23 00:22:34 by jaubry--         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# Directories
MEM_DIR		= $(SRCDIR)/mem_utils

# Source files
MEM_SRCS	= ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
			  ft_bzero.c ft_fbzero.c
SRCS		+= $(addprefix $(MEM_DIR)/, $(MEM_SRCS))

# VPATH
vpath %.c $(MEM_DIR)
