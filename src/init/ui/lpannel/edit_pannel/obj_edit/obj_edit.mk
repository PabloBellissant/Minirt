# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    obj_edit.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/18 19:17:20 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/19 12:12:48 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
OBJ_EDIT_DIR	= $(EDIT_PANNEL_DIR)/obj_edit

# Source files
OBJ_EDIT_SRCS	= populate_obj_edit.c
SRCS			+= $(addprefix $(OBJ_EDIT_DIR)/, $(OBJ_EDIT_SRCS))

OBJ_EDIT_MKS	= mat_edit/mat_edit.mk \
				  geometry_edit/geometry_edit.mk
include $(addprefix $(OBJ_EDIT_DIR)/, $(OBJ_EDIT_MKS))

# VPATH
vpath %.c $(OBJ_EDIT_DIR)
