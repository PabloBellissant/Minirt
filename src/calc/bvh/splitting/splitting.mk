# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    splitting.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/25 01:29:38 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/04 02:30:53 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SPLITTING_DIR	= $(BVH_DIR)/splitting

# Source files
SPLITTING_SRCS	= evaluate_split.c \
				  sort_prim.c key_obj_utils.c \
				  get_axis_split.c \
				  try_split.c

SRCS			+= $(addprefix $(SPLITTING_DIR)/, $(SPLITTING_SRCS))

SPLITTING_MKS	= med_prim/med_prim.mk \
				  med_space/med_space.mk \
				  sah/sah.mk

#sbvh/sbvh.mk

include $(addprefix $(SPLITTING_DIR)/, $(SPLITTING_MKS))

# VPATH
vpath %.c $(SPLITTING_DIR)
