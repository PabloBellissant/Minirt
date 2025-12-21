# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    phong_render.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:41:28 by pabellis          #+#    #+#              #
#    Updated: 2025/12/11 18:52:54 by pabellis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
PHONG_RENDER_DIR	= $(RAY_TRACING_DIR)/phong_render

# Source files
PHONG_RENDER_SRCS	= phong_render.c \
					  sample_colors.c \
					  hit_register_light.c \
					  hit_light_plane.c

SRCS				+= $(addprefix $(PHONG_RENDER_DIR)/, $(PHONG_RENDER_SRCS))

# VPATH
vpath %.c $(PHONG_RENDER_DIR)
