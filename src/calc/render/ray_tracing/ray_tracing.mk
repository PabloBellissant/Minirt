# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ray_tracing.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:41:28 by pabellis          #+#    #+#              #
#    Updated: 2025/12/11 18:52:54 by pabellis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
RAY_TRACING_DIR	= $(RENDER_DIR)/ray_tracing

# Source files
RAY_TRACING_SRCS	= cast_rays.c \
					  intersect.c \
					  draw_skybox.c \
					  draw_on_screen.c \
					  normal_debug.c \
					  sample_texture.c \
					  reflect.c \
					  fill_uv_normal.c
SRCS				+= $(addprefix $(RAY_TRACING_DIR)/, $(RAY_TRACING_SRCS))

RAY_TRACING_MKS	= phong_render/phong_render.mk \
				  refract/refract.mk \
				  pbr_render/pbr_render.mk \
				  monte_carlo/monte_carlo.mk

include $(addprefix $(RAY_TRACING_DIR)/, $(RAY_TRACING_MKS))


# VPATH
vpath %.c $(RAY_TRACING_DIR)
