# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    bvh_debug.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/07 20:01:51 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/07 20:02:48 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
BVH_DEBUG_DIR	= $(BVH_DIR)/bvh_debug

# Source files
BVH_DEBUG_SRCS	= bvh_debug.c \
				  bvh_debug_align.c \
				  bvh_debug_bounds.c \
				  bvh_debug_config.c \
				  bvh_debug_header.c \
				  bvh_debug_print.c \
				  bvh_debug_stats.c \
				  bvh_debug_tree.c

SRCS			+= $(addprefix $(BVH_DEBUG_DIR)/, $(BVH_DEBUG_SRCS))

# VPATH
vpath %.c $(BVH_DEBUG_DIR)
