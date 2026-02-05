# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    export_scene.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:54:33 by jaubry--          #+#    #+#              #
#    Updated: 2025/12/09 15:43:16 by pabellis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
EXPORT_SCENE_DIR	= $(SRCDIR)/export_scene

# Source files
EXPORT_SCENE_SRCS	= export_scene.c \
					  write_base.c \
					  write_lights.c \
					  write_materials.c \
					  write_objects.c \
					  write_primitives.c

SRCS			+= $(addprefix $(EXPORT_SCENE_DIR)/, $(EXPORT_SCENE_SRCS))


# VPATH
vpath %.c $(EXPORT_SCENE_DIR)
