# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sphere.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/25 01:28:27 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/03 03:12:59 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
NEW_SPHERE_DIR		= $(SHAPE_DIR)/sphere

# Source files
NEW_SPHERE_SRCS		= evaluate_bounds_sphere.c \
					  get_sphere_surface.c

SRCS				+= $(addprefix $(NEW_SPHERE_DIR)/, $(NEW_SPHERE_SRCS))

# VPATH
vpath %.c $(NEW_SPHERE_DIR)
