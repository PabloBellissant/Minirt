# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    type.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:41:28 by pabellis          #+#    #+#              #
#    Updated: 2025/12/12 03:22:57 by pabellis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
MTL_TYPE_DIR	= $(MTL_DIR)/type

# Source files
MTL_TYPE_SRCS	= newmtl.c \
			  ns.c \
			  ka.c \
			  kd.c \
			  ks.c \
			  map_kd.c \
			  map_bump.c \
			  map_pr.c \
			  map_ka.c \
			  map_d.c \
			  d.c \
			  pr.c \
			  ke.c \
			  ni.c \
			  pm.c

SRCS		+= $(addprefix $(MTL_TYPE_DIR)/, $(MTL_TYPE_SRCS))

# VPATH
vpath %.c $(MTL_TYPE_DIR)
