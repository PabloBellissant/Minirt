# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    render.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:39:51 by jaubry--          #+#    #+#              #
#    Updated: 2025/08/05 01:52:31 by jaubry--         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# Directories
RENDER_DIR	= $(CALC_DIR)/render

# Source files
RENDER_SRCS	=

SRCS		+= $(addprefix $(RENDER_DIR)/, $(RENDER_SRCS))

RENDER_MKS	= rasterization/rasterization.mk \
			  ray_tracing/ray_tracing.mk

include $(addprefix $(RENDER_DIR)/, $(RENDER_MKS))

# VPATH
vpath %.c $(RENDER_DIR)
