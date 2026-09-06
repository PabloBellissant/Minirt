# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mat_edit.mk                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/18 19:19:10 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/18 19:21:00 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
MAT_EDIT_DIR	= $(OBJ_EDIT_DIR)/mat_edit

# Source files
MAT_EDIT_SRCS	= populate_mat_edit.c \
				  is_tex_editable.c \
				  add_d_edit.c \
				  add_ka_edit.c \
				  add_kd_edit.c \
				  add_ks_edit.c \
				  add_ni_edit.c \
				  add_ns_edit.c \
				  add_pm_edit.c \
				  add_pr_edit.c
SRCS			+= $(addprefix $(MAT_EDIT_DIR)/, $(MAT_EDIT_SRCS))

# VPATH
vpath %.c $(MAT_EDIT_DIR)
