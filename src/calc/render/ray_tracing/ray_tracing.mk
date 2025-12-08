# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ray_tracing.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:41:28 by pabellis          #+#    #+#              #
#    Updated: 2025/08/04 23:24:24 by pabellis         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# Directories
RAY_TRACING_DIR	= $(RENDER_DIR)/ray_tracing

# Source files
RAY_TRACING_SRCS	= cast_rays.c \
					  intersect.c \
					  sample_materials.c \
					  draw_skybox.c \
					  intersect_shadow.c \
					  shade.c

SRCS				+= $(addprefix $(RAY_TRACING_DIR)/, $(RAY_TRACING_SRCS))

# VPATH
vpath %.c $(RAY_TRACING_DIR)
