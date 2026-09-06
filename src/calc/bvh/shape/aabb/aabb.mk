# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    aabb.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/25 01:27:22 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/03 03:12:30 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
NEW_AABB_DIR		= $(SHAPE_DIR)/aabb

# Source files
NEW_AABB_SRCS	= evaluate_bounds_aabb.c \
				  get_aabb_surface.c

SRCS		+= $(addprefix $(NEW_AABB_DIR)/, $(NEW_AABB_SRCS))

# VPATH
vpath %.c $(NEW_AABB_DIR)
