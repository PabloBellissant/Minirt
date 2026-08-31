# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    lpannel.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/18 19:12:22 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/18 19:13:46 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
LPANNEL_DIR		= $(UI_DIR)/lpannel

# Source files
LPANNEL_SRCS	= init_lpannel.c \
				  add_lpannel_switch.c
SRCS			+= $(addprefix $(LPANNEL_DIR)/, $(LPANNEL_SRCS))

LPANNEL_MKS		= scene_list/scene_list.mk \
				  edit_pannel/edit_pannel.mk
include $(addprefix $(LPANNEL_DIR)/, $(LPANNEL_MKS))

# VPATH
vpath %.c $(LPANNEL_DIR)
