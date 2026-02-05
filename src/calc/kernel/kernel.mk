# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    kernel.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:39:51 by jaubry--          #+#    #+#              #
#    Updated: 2025/08/05 01:52:31 by jaubry--         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

# Directories
KERNEL_DIR	= $(CALC_DIR)/kernel

# Source files
KERNEL_SRCS	= monte_carlo_kernel.c\
			  normal_kernel.c \
			  pbr_kernel.c \
			  phong_kernel.c \
			  accu_kernel.c \
			  heat_kernel.c

SRCS		+= $(addprefix $(KERNEL_DIR)/, $(KERNEL_SRCS))


# VPATH
vpath %.c $(KERNEL_DIR)
