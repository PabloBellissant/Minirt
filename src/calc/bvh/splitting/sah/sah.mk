# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sah.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/27 05:33:57 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/05 02:42:04 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SAH_DIR		= $(SPLITTING_DIR)/sah

# Source files
SAH_SRCS	= sah.c \
			  sah_bins.c sah_bins_cost.c \
			  sah_bounds.c sah_merge_bounds.c \
			  sah_plan.c \
			  sah_cost.c

SRCS		+= $(addprefix $(SAH_DIR)/, $(SAH_SRCS))

# VPATH
vpath %.c $(SAH_DIR)
