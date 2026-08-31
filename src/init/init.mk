# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    init.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/05 16:00:47 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/18 19:42:50 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
INIT_DIR	= $(SRCDIR)/init

# Source files
INIT_SRCS	= init_graphics.c
SRCS		+= $(addprefix $(INIT_DIR)/, $(INIT_SRCS))

# MKs
MKS			= ui/ui.mk
include	$(addprefix $(INIT_DIR)/, $(MKS))

# VPATH
vpath %.c $(INIT_DIR)
