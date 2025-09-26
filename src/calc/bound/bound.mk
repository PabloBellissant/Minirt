# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    bound.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:31:40 by pabellis          #+#    #+#              #
#    Updated: 2025/07/22 18:37:04 by pabellis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
BOUND_DIR		= $(CALC_DIR)/bound

# Source files
BOUND_SRCS	= draw_bound.c \
			  calc_bvh_bound.c \
			  calc_aabb_bound.c \
			  calc_sphere_bound.c \
			  apply_bound.c

SRCS		+= $(addprefix $(BOUND_DIR)/, $(BOUND_SRCS))

# VPATH
vpath %.c $(BOUND_DIR)
