# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    objects.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:43:32 by jaubry--          #+#    #+#              #
#    Updated: 2025/07/31 21:14:17 by jaubry--         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# Directories
OBJECTS_DIR		= $(CALC_DIR)/objects

# Source files
OBJECTS_SRCS	= hit_cylinder.c \
				  hit_sphere.c \
				  hit_plane.c
SRCS			+= $(addprefix $(OBJECTS_DIR)/, $(OBJECTS_SRCS))

# VPATH
vpath %.c $(OBJECTS_DIR)
