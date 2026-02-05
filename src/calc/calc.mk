# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    calc.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:39:51 by jaubry--          #+#    #+#              #
#    Updated: 2026/01/19 14:48:44 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
CALC_DIR	= $(SRCDIR)/calc

# Source files
CALC_SRCS	= utils.c
SRCS		+= $(addprefix $(CALC_DIR)/, $(CALC_SRCS))

CALC_MKS	= bvh/bvh.mk \
			  render/render.mk \
			  kernel/kernel.mk

include $(addprefix $(CALC_DIR)/, $(CALC_MKS))

# VPATH
vpath %.c $(CALC_DIR)
