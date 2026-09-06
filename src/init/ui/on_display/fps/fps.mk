# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    fps.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/18 19:10:08 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/18 19:12:03 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
FPS_DIR			= $(ON_DISPLAY_DIR)/fps

# Source files
FPS_SRCS		= add_fps.c \
				  update_fps.c \
				  fps_counter.c
SRCS			+= $(addprefix $(FPS_DIR)/, $(FPS_SRCS))

# VPATH
vpath %.c $(FPS_DIR)
