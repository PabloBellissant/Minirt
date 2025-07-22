# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    bvh.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:41:28 by jaubry--          #+#    #+#              #
#    Updated: 2025/07/22 21:52:56 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
BVH_DIR		= $(CALC_DIR)/bvh

# Source files
BVH_SRCS	= create_bvh.c \
			  get_bvh_area.c get_next_bvh_area.c \
			  get_object_count.c \
			  merge_bvh.c merge_nearest_bvh.c \
			  hit_bvh.c
SRCS		+= $(addprefix $(BVH_DIR)/, $(BVH_SRCS))

# VPATH
vpath %.c $(BVH_DIR)
