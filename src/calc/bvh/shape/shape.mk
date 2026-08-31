# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    shape.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/25 01:22:06 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/03 03:11:01 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SHAPE_DIR		= $(BVH_DIR)/shape

# Source files
SHAPE_SRCS	= evaluate_bounds.c \
			  get_bounds_surface.c

SRCS		+= $(addprefix $(SHAPE_DIR)/, $(SHAPE_SRCS))

SHAPE_MKS	= aabb/aabb.mk \
			  sphere/sphere.mk \
			  obb/obb.mk

include $(addprefix $(SHAPE_DIR)/, $(SHAPE_MKS))

# VPATH
vpath %.c $(SHAPE_DIR)
