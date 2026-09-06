# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    edit_pannel.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/18 19:15:30 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/20 14:19:58 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
EDIT_PANNEL_DIR		= $(LPANNEL_DIR)/edit_pannel

# Source files
EDIT_PANNEL_SRCS	= init_edit_pannel.c \
					  destroy_edit_pannel.c \
					  populate_inner_edit.c \
					  rebuild_inner_edit.c
SRCS				+= $(addprefix $(EDIT_PANNEL_DIR)/, $(EDIT_PANNEL_SRCS))

EDIT_PANNEL_MKS		= blocks/blocks.mk \
					  obj_edit/obj_edit.mk \
					  render_edit/render_edit.mk
include $(addprefix $(EDIT_PANNEL_DIR)/, $(EDIT_PANNEL_MKS))

# VPATH
vpath %.c $(EDIT_PANNEL_DIR)
