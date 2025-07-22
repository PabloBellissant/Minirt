# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    draw.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:37:45 by jaubry--          #+#    #+#              #
#    Updated: 2025/07/22 18:39:11 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
DRAW_DIR		= $(SRCDIR)/draw

# Source files
DRAW_SRCS		= draw_bvh.c \
				  draw_line.c \
				  put_pixel.c \
				  rasterization.c
SRCS			+= $(addprefix $(DRAW_DIR)/, $(DRAW_SRCS))

# VPATH
vpath %.c $(DRAW_DIR)
