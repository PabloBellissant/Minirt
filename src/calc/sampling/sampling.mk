# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sampling.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabellis <pabellis@student.forty2.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:31:40 by pabellis          #+#    #+#              #
#    Updated: 2025/07/22 18:37:04 by pabellis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SAMPLING_DIR	= $(CALC_DIR)/sampling

# Source files
SAMPLING_SRCS	= draw_supersampling.c

SRCS		+= $(addprefix $(SAMPLING_DIR)/, $(SAMPLING_SRCS))

# VPATH
vpath %.c $(SAMPLING_DIR)
