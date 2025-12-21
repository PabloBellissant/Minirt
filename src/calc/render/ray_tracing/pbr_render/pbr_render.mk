# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    pbr_render.mk                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:41:28 by pabellis          #+#    #+#              #
#    Updated: 2025/12/11 18:52:54 by pabellis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
PBR_RENDER_DIR	= $(RAY_TRACING_DIR)/pbr_render

# Source files
PBR_RENDER_SRCS	= sample_materials.c \
				  get_color_through.c

SRCS				+= $(addprefix $(PBR_RENDER_DIR)/, $(PBR_RENDER_SRCS))

# VPATH
vpath %.c $(PBR_RENDER_DIR)
