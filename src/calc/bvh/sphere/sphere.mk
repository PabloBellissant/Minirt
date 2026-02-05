# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sphere.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:41:28 by pabellis          #+#    #+#              #
#    Updated: 2025/08/04 23:24:24 by pabellis         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# Directories
SPHERE_DIR		= $(BVH_DIR)/sphere

# Source files
SPHERE_SRCS	= create_sphere_bvh.c \
			  merge_nearest_sphere_bvh.c \
			  get_next_sphere_bvh_area.c \
			  merge_sphere_bvh.c \
			  get_sphere_root.c

SRCS		+= $(addprefix $(SPHERE_DIR)/, $(SPHERE_SRCS))

# VPATH
vpath %.c $(SPHERE_DIR)
