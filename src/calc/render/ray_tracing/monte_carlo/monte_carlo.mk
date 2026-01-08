# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    monte_carlo.mk                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabellis <pabellis@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:41:28 by pabellis          #+#    #+#              #
#    Updated: 2025/12/11 18:52:54 by pabellis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
MONTE_CARLO_DIR	= $(RAY_TRACING_DIR)/monte_carlo

# Source files
MONTE_CARLO_SRCS	= monte_carlo_render.c \
					  path_shade.c \
					  path_sample_materials.c \
					  random.c \
					  rand_vec.c

SRCS				+= $(addprefix $(MONTE_CARLO_DIR)/, $(MONTE_CARLO_SRCS))

# VPATH
vpath %.c $(MONTE_CARLO_DIR)
