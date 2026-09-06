# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    obb.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/29 09:47:25 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/03 03:12:40 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
OBB_DIR		= $(SHAPE_DIR)/obb

# Source files
OBB_SRCS	= evaluate_bounds_obb.c \
			  basis3_from_eigh.c \
			  mat3_eigh_jacobi.c \
			  get_pca_covariance.c get_pca_mean.c \
			  quat_from_mat3.c \
			  get_obb_projected_spread.c \
			  get_obb_surface.c

SRCS		+= $(addprefix $(OBB_DIR)/, $(OBB_SRCS))

# VPATH
vpath %.c $(OBB_DIR)
