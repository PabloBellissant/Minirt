# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    bvh_utils.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/03 02:52:15 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/05 02:29:37 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
BVH_UTILS_DIR	= $(BVH_DIR)/bvh_utils

# Source files
BVH_UTILS_SRCS	= cuboid_utils.c cuboid_constructors.c cuboid_operations.c \
				  cuboid_union.c cuboid_union_getters.c \
				  get_primitives_mean.c \
				  get_primitives_variance.c \
				  axes_project.c mat3_project.c

SRCS			+= $(addprefix $(BVH_UTILS_DIR)/, $(BVH_UTILS_SRCS))

# VPATH
vpath %.c $(BVH_UTILS_DIR)
