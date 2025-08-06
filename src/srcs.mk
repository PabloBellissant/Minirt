# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    srcs.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+         #
#              +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:20:57 by jaubry--          #+#    #+#              #
#    Updated: 2025/07/22 21:53:37 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
INIT_DIR	= $(SRCDIR)/init

# Source files
MINIRT_SRCS	= main.c \
			  loop.c loop_hook.c \
			  camera_utils.c camera_move.c \
			  clear_scene.c
INIT_SRCS	= init_graphics.c
SRCS		+= $(addprefix $(SRCDIR)/, $(MINIRT_SRCS)) \
			   $(addprefix $(INIT_DIR)/, $(INIT_SRCS))

# MKs
MKS			= parsing/parsing.mk \
			  draw/draw.mk \
			  calc/calc.mk

include	$(addprefix $(SRCDIR)/, $(MKS))

# VPATH
vpath %.c $(SRCDIR) $(INIT_DIR)
