# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    alloc.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/08 08:58:19 by jaubry--          #+#    #+#              #
#    Updated: 2025/03/12 17:51:09 by lmarcucc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
ALLOC_DIR	= $(SRCDIR)/alloc

# Source files
ALLOC_SRCS	= ft_calloc.c ft_realloc.c ft_free.c
SRCS		+= $(addprefix $(ALLOC_DIR)/, $(ALLOC_SRCS))

# VPATH
vpath %.c $(ALLOC_DIR)
