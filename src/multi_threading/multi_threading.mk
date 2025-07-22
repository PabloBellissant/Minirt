# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    multi_threading.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 18:31:40 by jaubry--          #+#    #+#              #
#    Updated: 2025/07/22 18:37:04 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories

MTHR_DIR	= $(SRCDIR)/multi_threading
STACK_DIR	= $(MTHR_DIR)/task_stack

# Source files
STACK_SRCS	= dequeue.c enqueue.c
MTHR_SRCS	= init_threads.c kill_threads.c routine.c
SRCS		+= $(addprefix $(MTHR_DIR)/, $(MTHR_SRCS)) \
			   $(addprefix $(STACK_DIR)/, $(STACK_SRCS))

# VPATH
vpath %.c $(STACK_DIR) $(MTHR_DIR)
