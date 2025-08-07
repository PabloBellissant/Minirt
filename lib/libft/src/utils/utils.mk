# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    utils.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/08 09:14:34 by jaubry--          #+#    #+#              #
#    Updated: 2025/08/07 07:03:21 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
UTILS_DIR	= $(SRCDIR)/utils

# Source files
UTILS_SRCS	= time_utils.c \
			  quad_bezier_utils.c
SRCS		+= $(addprefix $(UTILS_DIR)/, $(UTILS_SRCS))

# VPATH
vpath %.c $(UTILS_DIR)
