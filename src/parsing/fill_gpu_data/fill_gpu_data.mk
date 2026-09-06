# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    fill_gpu_data.mk                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 19:25:14 by jaubry--          #+#    #+#              #
#    Updated: 2025/07/22 21:55:38 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
FILL_GPU_DATA_DIR	= $(PARSING_DIR)/fill_gpu_data

# Source files
FILL_GPU_DATA_SRCS	= fill_gpu_data.c \
					  fill_object_mem.c \
					  fill_texture.c

SRCS			+= $(addprefix $(FILL_GPU_DATA_DIR)/, $(FILL_GPU_DATA_SRCS))

# VPATH
vpath %.c $(FILL_GPU_DATA_DIR) $(FILL_GPU_DATA_DIR)
