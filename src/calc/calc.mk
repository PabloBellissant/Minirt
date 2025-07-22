# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    calc.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:39:51 by jaubry--          #+#    #+#              #
#    Updated: 2025/07/22 21:47:02 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
CALC_DIR	= $(SRCDIR)/calc

# Source files
CALC_SRCS	= hit_register.c \
			  ray_path.c
SRCS		+= $(addprefix $(CALC_DIR)/, $(CALC_SRCS))

CALC_MKS	= bvh/bvh.mk \
			  objects/objects.mk

include $(addprefix $(CALC_DIR)/, $(CALC_MKS))

# VPATH
vpath %.c $(CALC_DIR)
