# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    str_utils.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmarcucc <lucas@student.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/08 09:14:34 by jaubry--          #+#    #+#              #
#    Updated: 2025/03/19 19:55:55 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
STR_DIR		= $(SRCDIR)/str_utils

# Source files
STR_SRCS	= ft_strlen.c \
			  ft_strtrim.c ft_strcrop.c \
			  ft_strrchr.c ft_strchr.c ft_substr.c \
			  ft_strdup.c ft_strndup.c \
			  ft_strcmp.c ft_strncmp.c ft_strrncmp.c \
			  ft_strstr.c ft_strnstr.c \
			  ft_strlcat.c ft_strlcpy.c \
			  ft_striteri.c ft_strmapi.c \
			  ft_strjoin.c freejoin.c dfreejoin.c ft_strjoin_all.c
SRCS		+= $(addprefix $(STR_DIR)/, $(STR_SRCS))

# VPATH
vpath %.c $(STR_DIR)
