# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    bvh.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:41:28 by jaubry--          #+#    #+#              #
#    Updated: 2025/08/04 23:24:24 by jaubry--         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# Directories
BVH_DIR		= $(CALC_DIR)/bvh

# Source files
BVH_SRCS	= create_bvh.c \
			  get_next_bvh_area.c \
			  merge_bvh.c \
			  merge_nearest_bvh.c \
			  hit_bvh.c \
			  hit_box_bvh.c
SRCS		+= $(addprefix $(BVH_DIR)/, $(BVH_SRCS))

# VPATH
vpath %.c $(BVH_DIR)
