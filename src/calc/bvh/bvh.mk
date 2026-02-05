# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    bvh.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:41:28 by jaubry--          #+#    #+#              #
#    Updated: 2026/01/20 16:29:03 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
BVH_DIR		= $(CALC_DIR)/bvh

# Source files
BVH_SRCS	= get_bvh_count.c \
			  is_bvh_full.c \
			  load_bvh.c \
			  get_min_max.c \
			  quick_sort.c \
			  compare_function.c \
			  get_object.c \
			  get_area.c

SRCS		+= $(addprefix $(BVH_DIR)/, $(BVH_SRCS))

BVH_MKS	= aabb/aabb.mk \
		  sphere/sphere.mk \
		  sah/sah.mk \
		  bvh_ary/bvh_ary.mk

include $(addprefix $(BVH_DIR)/, $(BVH_MKS))

# VPATH
vpath %.c $(BVH_DIR)
