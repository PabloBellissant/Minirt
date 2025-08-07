# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/27 01:19:17 by jaubry--          #+#    #+#              #
#    Updated: 2025/08/07 03:25:30 by jaubry--         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/bash

# Print utils
include colors.mk

# Variables
DEBUG		= $(if $(filter debug,$(MAKECMDGOALS)),1,0)
SILENCE		= 2>/dev/null

# Directories
SRCDIR		= src
OBJDIR		= .obj
DEPDIR		= .dep
INCDIR		= include

# Output
NAME		= libft.a

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror $(if $(filter 1,$(DEBUG)),-g3) -D DEBUG=$(DEBUG)
DFLAGS		= -MMD -MP -MF $(DEPDIR)/$*.d
IFLAGS		= -I$(INCDIR)
CF			= $(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS)

AR          = $(if $(findstring -flto,$(CC)),llvm-ar-12,ar) $(SILENCE)
ARFLAGS		= rcs
RANLIB      = $(if $(findstring -flto,$(CC)),llvm-ranlib-12,ranlib) $(SILENCE)

# VPATH
vpath %.h $(INCDIR)
vpath %.o $(OBJDIR)
vpath %.d $(DEPDIR)

# Sources
MKS			= io/io.mk alloc/alloc.mk parsing/parsing.mk \
			  conversion/conversion.mk mem_utils/mem_utils.mk \
			  str_utils/str_utils.mk strr_utils/strr_utils.mk \
			  data_structs/data_structs.mk utils/utils.mk

include $(addprefix $(SRCDIR)/, $(MKS))

OBJS		= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
DEPS		= $(addprefix $(DEPDIR)/, $(notdir $(SRCS:.o=.d)))
INCLUDES	= libft.h ft_printfs_utils.h get_next_line_utils.h



all: $(NAME)

debug: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(ARFLAGS) $@ $^
	@$(if $(findstring -flto,$(CC)),@$(RANLIB) $@,)
ifeq ($(DEBUG), 1)
	$(call color,$(ORANGE)$(BOLD),"✓ %UL%$(NAME)%NUL% debug build complete")
else
	$(call color,$(GREEN)$(BOLD),"✓ Library %UL%$(NAME)%NUL% successfully created")
endif

$(OBJDIR)/%.o: %.c | buildmsg $(OBJDIR) $(DEPDIR)
	$(call color,$(BLUE),"➜ Compiling %UL%libft/$<")
	@$(CF) -c $< -o $@

$(OBJDIR) $(DEPDIR):
	$(call color,$(CYAN),"Creating directory %UL%libft/$@")
	@mkdir -p $@

buildmsg:
ifneq ($(shell [ -f $(NAME) ] && echo exists),exists)
ifeq ($(DEBUG),1)
	$(call color,$(YELLOW)$(BOLD),"$(NL)⚠ Building debug library %UL%$(NAME)%NUL%...")
else
	$(call color,$(PURPLE)$(BOLD),"$(NL)Creating library %UL%$(NAME)%NUL%...")
endif
endif

help:
	@echo "Available targets:"
	@echo "  all     : Build the library"
	@echo "  clean   : Remove object files"
	@echo "  fclean  : Remove object files and library"
	@echo "  re      : Rebuild everything"

clean:
	$(call color,$(RED),"Cleaning %UL%libft%NUL% object files from %UL%$(OBJDIR)%NUL% and %UL%$(DEPDIR)")
	@rm -rf $(OBJDIR) $(DEPDIR)

fclean: clean
	$(call color,$(RED),"Removing library %UL%$(NAME)")
	@rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re debug help buildmsg
