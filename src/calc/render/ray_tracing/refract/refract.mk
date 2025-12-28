# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    refract.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:41:28 by pabellis          #+#    #+#              #
#    Updated: 2025/12/11 18:52:54 by pabellis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
REFRACT_DIR	= $(RAY_TRACING_DIR)/refract

# Source files
REFRACT_SRCS	= refract.c \
				  refract_triangle.c \
				  refract_sphere.c \
				  refract_plane.c

SRCS				+= $(addprefix $(REFRACT_DIR)/, $(REFRACT_SRCS))

# VPATH
vpath %.c $(REFRACT_DIR)
