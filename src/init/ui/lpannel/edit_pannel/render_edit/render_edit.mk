# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    render_edit.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/19 11:01:25 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/19 20:29:20 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
RENDER_EDIT_DIR		= $(EDIT_PANNEL_DIR)/render_edit

# Source files
RENDER_EDIT_SRCS	= populate_render_edit.c \
					  populate_cam_params.c \
					  populate_export.c
SRCS				+= $(addprefix $(RENDER_EDIT_DIR)/, $(RENDER_EDIT_SRCS))

# VPATH
vpath %.c $(RENDER_EDIT_DIR)
