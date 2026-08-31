# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    blocks.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/18 19:22:36 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/18 19:45:37 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
BLOCKS_DIR		= $(EDIT_PANNEL_DIR)/blocks

BLOCKS_MKS		= base \
				  form \
				  slider \
				  colorpicker
include $(foreach n,$(BLOCKS_MKS),$(BLOCKS_DIR)/$(n)/$(n)_blocks.mk)
