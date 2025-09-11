# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    aabb.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:41:28 by pabellis          #+#    #+#              #
#    Updated: 2025/08/04 23:24:24 by pabellis         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# Directories
AABB_DIR		= $(BVH_DIR)/aabb

# Source files
AABB_SRCS	= create_bvh.c \
			  get_next_bvh_area.c \
			  merge_bvh.c \
			  merge_nearest_bvh.c

SRCS		+= $(addprefix $(AABB_DIR)/, $(AABB_SRCS))

# VPATH
vpath %.c $(AABB_DIR)
