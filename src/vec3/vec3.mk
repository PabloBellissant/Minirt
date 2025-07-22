# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    vec3.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:26:12 by jaubry--          #+#    #+#              #
#    Updated: 2025/07/22 21:53:50 by jaubry--         ###   ########.fr        #
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
			  vec3_unit.c
SRCS		+= $(addprefix $(VEC3_DIR)/, $(VEC3_SRCS))

# VPATH
vpath %.c $(VEC3_DIR)
