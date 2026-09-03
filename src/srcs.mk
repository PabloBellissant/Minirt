# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    srcs.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+         #
#              +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:20:57 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/20 17:02:11 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Source files
MINIRT_SRCS	= main.c loop.c \
			  setup_hooks.c mouse_hooks.c key_hooks.c \
			  params_hooks1.c params_hooks2.c params_hooks3.c \
			  camera_utils.c camera_move.c \
			  clear_scene.c \
			  register_rt_errors.c \
			  export_to_ppm.c \
			  opencl.c \
			  free_utils.c \
			  render_task.c

SRCS		+= $(addprefix $(SRCDIR)/, $(MINIRT_SRCS))

# MKs
MKS			= parsing/parsing.mk \
			  calc/calc.mk \
			  init/init.mk \
			  export_scene/export_scene.mk

include	$(addprefix $(SRCDIR)/, $(MKS))

# VPATH
vpath %.c $(SRCDIR)
