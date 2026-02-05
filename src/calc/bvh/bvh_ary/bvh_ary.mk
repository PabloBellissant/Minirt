# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    bvh_ary.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/20 16:27:54 by jaubry--          #+#    #+#              #
#    Updated: 2026/01/20 16:28:49 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
BVH_ARY_DIR		= $(BVH_DIR)/bvh_ary

# Source files
BVH_ARY_SRCS	= bvh4.c bvh8.c bvh_cleanup.c

SRCS		+= $(addprefix $(BVH_ARY_DIR)/, $(BVH_ARY_SRCS))

# VPATH
vpath %.c $(BVH_ARY_DIR)
