# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    rasterization.mk                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:41:28 by jaubry--          #+#    #+#              #
#    Updated: 2025/08/04 23:24:24 by jaubry--         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# Directories
RASTERIZATION_DIR	= $(CALC_DIR)/rasterization

# Source files
RASTERIZATION_SRCS	= rasterize_bvh.c \
					  projection_matrix.c
SRCS				+= $(addprefix $(RASTERIZATION_DIR)/, $(RASTERIZATION_SRCS))

# VPATH
vpath %.c $(RASTERIZATION_DIR)
