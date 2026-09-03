# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    bvh.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:41:28 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/07 20:01:11 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
BVH_DIR		= $(CALC_DIR)/bvh

# Source files
BVH_SRCS	= create_bvh.c \
				  bvh_subdivide.c \
				  rasterize_bvh.c \
				  free_bvh.c \
				  index_bvh.c \
				  create_global_bvh.c

SRCS		+= $(addprefix $(BVH_DIR)/, $(BVH_SRCS))

BVH_MKS	= shape/shape.mk \
			  splitting/splitting.mk \
			  bvh_utils/bvh_utils.mk \
			  bvh_debug/bvh_debug.mk

include $(addprefix $(BVH_DIR)/, $(BVH_MKS))

# VPATH
vpath %.c $(BVH_DIR)
