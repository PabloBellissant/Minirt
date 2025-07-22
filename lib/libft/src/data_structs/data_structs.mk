# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    data_structs.mk                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/08 08:59:31 by jaubry--          #+#    #+#              #
#    Updated: 2025/07/22 22:10:42 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
STRUCTS_DIR		= $(SRCDIR)/data_structs
LIST_DIR		= $(STRUCTS_DIR)/list
DLIST_DIR		= $(STRUCTS_DIR)/dlist
VECTOR_DIR		= $(STRUCTS_DIR)/vector

# Source files
LIST_SRCS	= ft_lstnew.c \
			  ft_lstsize.c \
			  ft_lstlast.c ft_lstgetindex.c \
			  ft_lstadd_front.c ft_lstadd_back.c ft_lstadd_after.c \
			  ft_lstdelone.c ft_lstclear.c ft_lstpop.c \
			  ft_lstiter.c ft_lstmap.c
LIST_SRCS	:= $(addprefix $(LIST_DIR)/, $(LIST_SRCS))

DLIST_SRCS	= ft_dlstnew.c \
			  ft_dlstsize.c \
			  ft_dlstfirst.c ft_dlstlast.c \
			  ft_dlstadd_front.c ft_dlstadd_back.c \
			  ft_dlstdelone.c ft_dlstclear.c \
			  ft_dlstiter.c ft_dlstmap.c \
			  ft_dlstindex.c ft_dlstget_index.c \
			  ft_dlstdup.c \
			  ft_dlstswap.c
DLIST_SRCS	:= $(addprefix $(DLIST_DIR)/, $(DLIST_SRCS))

VECTOR_SRCS	= vector_add.c \
			  vector_init.c \
			  vector_realloc.c \
			  set_vector_size.c \
			  remove_vector_elem.c \
			  get_vector_value.c \
			  free_vector.c
VECTOR_SRCS	:= $(addprefix $(VECTOR_DIR)/, $(VECTOR_SRCS))

SRCS		+= $(LIST_SRCS) $(DLIST_SRCS) $(VECTOR_SRCS)

# VPATH
vpath %.c $(LIST_DIR) $(DLIST_DIR) $(VECTOR_DIR)
