# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    calc.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:39:51 by jaubry--          #+#    #+#              #
#    Updated: 2025/08/05 01:52:31 by jaubry--         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# Directories
CALC_DIR	= $(SRCDIR)/calc

# Source files
CALC_SRCS	= hit_register.c \
			  hit_reg_plane.c \
			  ray_path.c \
			  phong_reflection.c
SRCS		+= $(addprefix $(CALC_DIR)/, $(CALC_SRCS))

CALC_MKS	= bvh/bvh.mk \
			  objects/objects.mk \
			  rasterization/rasterization.mk \
			  bound/bound.mk

include $(addprefix $(CALC_DIR)/, $(CALC_MKS))

# VPATH
vpath %.c $(CALC_DIR)
