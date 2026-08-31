# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    med_prim.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/25 01:30:36 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/12 01:04:53 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
MED_PRIM_DIR		= $(SPLITTING_DIR)/med_prim

# Source files
MED_PRIM_SRCS	= med_prim.c

SRCS		+= $(addprefix $(MED_PRIM_DIR)/, $(MED_PRIM_SRCS))

# VPATH
vpath %.c $(MED_PRIM_DIR)
