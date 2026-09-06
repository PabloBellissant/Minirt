# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    med_space.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/27 05:07:38 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/03 03:04:58 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
MED_SPACE_DIR		= $(SPLITTING_DIR)/med_space

# Source files
MED_SPACE_SRCS	= med_space.c \
				  get_med_space.c

SRCS		+= $(addprefix $(MED_SPACE_DIR)/, $(MED_SPACE_SRCS))

# VPATH
vpath %.c $(MED_SPACE_DIR)
