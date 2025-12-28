# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    calc.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:39:51 by jaubry--          #+#    #+#              #
#    Updated: 2025/12/10 19:59:26 by pabellis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
CALC_DIR	= $(SRCDIR)/calc

# Source files
CALC_SRCS	= utils.c \
			  hit_reg_plane.c
SRCS		+= $(addprefix $(CALC_DIR)/, $(CALC_SRCS))

CALC_MKS	= bvh/bvh.mk \
			  objects/objects.mk \
			  render/render.mk

include $(addprefix $(CALC_DIR)/, $(CALC_MKS))

# VPATH
vpath %.c $(CALC_DIR)
