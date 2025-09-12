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
BVH_SRCS	= hit_box_bvh.c \
			  get_bvh_count.c \
			  get_root.c \
			  is_bvh_full.c

SRCS		+= $(addprefix $(BVH_DIR)/, $(BVH_SRCS))

BVH_MKS	= aabb/aabb.mk \
		  sphere/sphere.mk

include $(addprefix $(BVH_DIR)/, $(BVH_MKS))

# VPATH
vpath %.c $(BVH_DIR)
