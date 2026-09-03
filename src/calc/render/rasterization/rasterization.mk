# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    rasterization.mk                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:41:28 by pabellis          #+#    #+#              #
#    Updated: 2026/02/12 01:01:45 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
RASTERIZATION_DIR	= $(RENDER_DIR)/rasterization

# Source files
RASTERIZATION_SRCS	= rasterize_cuboid.c \
					  rasterize_obb.c \
					  rasterize_sphere_outline.c \
					  get_cuboid_vertice.c \
					  rasterize_3d_line.c \
					  float_to_rainbow.c \
					  project_point.c \
					  rasterize_triangle_outline.c \
					  wireframe_render.c \
					  rasterize_outline_object.c \
					  rasterize_light_outline.c \
					  rasterize_plane_outline.c \
					  is_out_screen.c \
					  draw_circle.c \
					  rasterize_selected.c

SRCS				+= $(addprefix $(RASTERIZATION_DIR)/, $(RASTERIZATION_SRCS))

# VPATH
vpath %.c $(RASTERIZATION_DIR)
