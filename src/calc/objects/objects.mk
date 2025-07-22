# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    objects.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:43:32 by jaubry--          #+#    #+#              #
#    Updated: 2025/07/22 18:45:06 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
OBJECTS_DIR		= $(CALC_DIR)/objects

# Source files
OBJECTS_SRCS	= hit_cylinder.c \
				  hit_plane.c \
				  hit_sphere.c \
				  hit_triangle.c
SRCS			+= $(addprefix $(OBJECTS_DIR)/, $(OBJECTS_SRCS))

# VPATH
vpath %.c $(OBJECTS_DIR)
