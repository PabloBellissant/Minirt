# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    draw.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:37:45 by jaubry--          #+#    #+#              #
#    Updated: 2025/07/31 18:54:12 by jaubry--         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# Directories
DRAW_DIR		= $(SRCDIR)/draw

# Source files
DRAW_SRCS		= put_pixel.c
SRCS			+= $(addprefix $(DRAW_DIR)/, $(DRAW_SRCS))

# VPATH
vpath %.c $(DRAW_DIR)
