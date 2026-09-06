# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    geometry_edit.mk                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/18 19:21:13 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/20 11:26:52 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
GEOMETRY_EDIT_DIR	= $(OBJ_EDIT_DIR)/geometry_edit

# Source files
GEOMETRY_EDIT_SRCS	= populate_obj_geometry.c \
					  populate_sphere_geometry.c \
					  populate_plane_geometry.c
SRCS				+= $(addprefix $(GEOMETRY_EDIT_DIR)/, $(GEOMETRY_EDIT_SRCS))

# VPATH
vpath %.c $(GEOMETRY_EDIT_DIR)
