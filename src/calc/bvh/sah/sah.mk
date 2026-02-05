# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sah.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/19 14:46:53 by jaubry--          #+#    #+#              #
#    Updated: 2026/01/19 14:49:14 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SAH_DIR		= $(BVH_DIR)/sah

# Source files
SAH_SRCS	= bin_partitionning.c \
			  fill_bins.c \
			  get_axis_and_bin.c \
			  sah_algo.c sah_math.c \
			  sah_subdivide.c

SRCS		+= $(addprefix $(SAH_DIR)/, $(SAH_SRCS))

# VPATH
vpath %.c $(SAH_DIR)
