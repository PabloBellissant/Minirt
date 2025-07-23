# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    vec3.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:26:12 by jaubry--          #+#    #+#              #
#    Updated: 2025/07/23 22:48:59 by jaubry--         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# Directories

VEC3_DIR	= $(SRCDIR)/vec3

# Source files
VEC3_SRCS	= vec3_add.c \
			  vec3_add_scalar.c \
			  vec3_cross.c \
			  vec3_div_scalar.c \
			  vec3_dot.c \
			  vec3_length.c \
			  vec3_length_squared.c \
			  vec3_lerp.c \
			  vec3_random.c \
			  vec3_scale.c \
			  vec3_sub.c \
			  vec3_unit.c \
			  vec3_magnitude.c \
			  vec3_normalize.c \
			  vec3_mult.c
SRCS		+= $(addprefix $(VEC3_DIR)/, $(VEC3_SRCS))

# VPATH
vpath %.c $(VEC3_DIR)
