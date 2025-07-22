# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 17:43:39 by jaubry--          #+#    #+#              #
#    Updated: 2025/07/22 23:21:21 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL		:= /bin/bash

# Print utils
include colors.mk

# Variables
DEBUG		= $(if $(filter debug,$(MAKECMDGOALS)),1,0)
WIDTH		= 500
HEIGHT		= 500

# Directories
SRCDIR		= src
INCDIR		= include
OBJDIR		= .obj
DEPDIR		= .dep

LIBDIR		= lib
LIBFTDIR	= $(LIBDIR)/libft
MLXDIR		= $(LIBDIR)/minilibx-linux

# Output
NAME		= MiniRT
LIBFT		= $(LIBFTDIR)/libft.a
MLX			= $(MLXDIR)/libmlx.a

# Flags
CC			= cc
DEBUG_FLAGS	= -g3 -pg -Rpass-missed=.*
CFLAGS		= -Wall -Werror -Wextra \
			  -std=gnu11 \
			  $(if $(filter 1,$(DEBUG)),$(DEBUG_FLAGS)) \
			  -D DEBUG=$(DEBUG) \
			  -D WIDTH=$(WIDTH) \
			  -D HEIGHT=$(HEIGHT) \
			  -march=native -msse3
DFLAGS		= -MMD -MP -MF $(DEPDIR)/$*.d
IFLAGS		= -I$(INCDIR) -I$(LIBFTDIR)/include -I$(MLXDIR)
LFLAGS		= -L$(MLXDIR) -L$(LIBFTDIR) -lXext -lX11 -lm -lmlx -lft
CF			= $(CC) $(CFLAGS) $(IFLAGS)

# SRCS
include $(SRCDIR)/srcs.mk

OBJS		= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
DEPS		= $(addprefix $(DEPDIR)/, $(notdir $(SRCS:.c=.o)))

# VPATH
vpath %.h $(INCDIR) $(LIBFTDIR)/$(INCDIR) $(MLXDIR)
vpath %.o $(OBJDIR) $(LIBFTDIR)/$(OBJDIR)
vpath %.d $(DEPDIR) $(LIBFTDIR)/$(DEPDIR)

all: $(NAME)
debug: $(NAME)

fast: CFLAGS += -Ofast -march=native -mtune=native -flto -funroll-loops
fast: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	@$(CF) $^ $(LFLAGS) -o $@
ifeq ($(DEBUG),1)
	$(call color,$(ORANGE)$(BOLD),"✓ Debug build %UL%$@%NUL% complete")
else
	$(call color,$(GREEN)$(BOLD),"✓ Program %UL%$@%NUL% successfully created!")
endif

$(LIBFT):
	@$(MAKE) -s -C $(LIBFTDIR) $(if $(filter 1,$(DEBUG)),debug)

$(MLX):
	@echo -e "$(PURPLE)-> Building $(UNDERLINE)minilibx$(RESET)"
	@$(MAKE) -s -C $(MLXDIR)

$(OBJDIR)/%.o: %.c | $(OBJDIR) $(DEPDIR) buildmsg
	$(call color,$(BLUE),"➜ Compiling %UL%$<")
	@$(CF) $(DFLAGS) -c $< -o $@

$(OBJDIR) $(DEPDIR):
	$(call color,$(CYAN),"Creating directory %UL%$@")
	@mkdir -p $@

buildmsg:
ifneq ($(shell [ -f $(NAME) ] && echo exists),exists)
ifeq ($(DEBUG),1)
	$(call color,$(YELLOW)$(BOLD),"$(NL)⚠ Building %UL%$(NAME)%NUL% in debug mode...")
else
	$(call color,$(PURPLE),"$(NL)Creating program %UL%$(NAME)%NUL%...")
endif
endif

help:
	@echo "Available targets:"
	@echo -e "\tall, $(NAME)\t\t: Build the program"
	@echo -e "\tdebug\t\t\t\t: Build the program with debug symbols"
	@echo -e "\tre\t\t\t\t: Rebuild $(NAME)"
	@echo
	@echo -e "\tfast\t\t\t\t: Build the program with fast symbols"
	@echo
	@echo -e "\tclean\t\t\t\t: Remove object files"
	@echo -e "\tfclean\t\t\t\t: Remove object files, libraries and program"
	@echo
	@echo -e "\tprint-%\t\t\t\t: Prints makefile variable content when replacing '%'"

print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true

clean:
	@$(MAKE) -s -C $(LIBFTDIR) clean
	$(call color,$(RED),"Cleaning %UL%$(NAME)%NUL% object files from %UL%$(OBJDIR)%NUL% and %UL%$(DEPDIR)")
	@rm -rf $(OBJDIR) $(DEPDIR)

fclean: clean
	@$(MAKE) -s -C $(MLXDIR) clean
	@$(MAKE) -s -C $(LIBFTDIR) fclean
	$(call color,$(RED),"Cleaning %UL%$(NAME)%NUL% object files from %UL%$(OBJDIR)%NUL% and %UL%$(DEPDIR)")
	@rm -rf $(OBJDIR) $(DEPDIR)
	$(call color,$(RED),"Removing program %UL%$(NAME)")
	@rm -f $(NAME)

re: fclean all

refast: fclean fast

bonus: all

-include $(DEPS)

.PHONY: all debug fast refast re clean fclean help buildmsg print-%
