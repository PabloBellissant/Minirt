# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    rasterization.mk                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:41:28 by pabellis          #+#    #+#              #
#    Updated: 2025/08/04 23:24:24 by pabellis         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# Directories
RASTERIZATION_DIR	= $(RENDER_DIR)/rasterization

# Source files
RASTERIZATION_SRCS	= rasterize_cuboid.c \
					  rasterize_bvh.c \
					  rasterize_sphere_bvh.c \
					  rasterize_sphere_outline.c \
					  rasterize_cylinder_outline.c \
					  get_cuboid_vertice.c \
					  rasterize_3d_line.c \
					  float_to_rainbow.c \
					  project_point.c \
					  rasterize_triangle_outline.c \
					  outline_render.c \
					  rasterize_outline_object.c \
					  rasterize_light_outline.c \
					  rasterize_plane_outline.c \
					  is_out_screen.c \
					  draw_circle.c

SRCS				+= $(addprefix $(RASTERIZATION_DIR)/, $(RASTERIZATION_SRCS))

# VPATH
vpath %.c $(RASTERIZATION_DIR)
