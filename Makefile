# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 17:43:39 by jaubry--          #+#    #+#              #
#    Updated: 2025/08/07 09:45:01 by jaubry--         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SHELL		:= /bin/bash

# Print utils
include colors.mk

# Variables
FAST		= $(if $(filter fast,$(MAKECMDGOALS)),1,0)
DEBUG		= $(if $(filter debug,$(MAKECMDGOALS)),1,0)
WINDOWLESS	= 0
FULLSCREEN	= 0
ifeq ($(FULLSCREEN), 1)
WIDTH		= 1920
HEIGHT		= 1080
else
WIDTH		= 500
HEIGHT		= 500
endif
PERF		= 0

# Directories
SRCDIR		= src
INCDIR		= include
OBJDIR		= .obj
DEPDIR		= .dep

LIBDIR		= lib
LIBFTDIR	= $(LIBDIR)/libft
MLXDIR		= $(LIBDIR)/minilibx-linux
MLXWDIR		= $(LIBDIR)/mlx_wrapper
FONT_RENDIR	= $(LIBDIR)/font_renderer

# Output
NAME		= MiniRT
LIBFT		= $(LIBFTDIR)/libft.a
MLX			= $(MLXDIR)/libmlx.a
MLXW		= $(MLXWDIR)/libmlx-wrapper.a
FONT_RENDER	= $(FONT_RENDIR)/libfont-renderer.a

# Flags
CC			= cc
DEBUG_FLAGS	= -g3
#-pg -Rpass-missed=.*
CFLAGS		= -Wall -Werror -Wextra \
			  -std=gnu11 \
			  $(if $(filter 1,$(DEBUG)),$(DEBUG_FLAGS)) \
			  -D DEBUG=$(DEBUG) \
			  -D WIDTH=$(WIDTH) \
			  -D HEIGHT=$(HEIGHT) \
			  -D PERF=$(PERF) \
			  -D FULLSCREEN=$(FULLSCREEN) \
			  -D WINDOWLESS=$(WINDOWLESS) \
			  -msse3
DFLAGS		= -MMD -MP -MF $(DEPDIR)/$*.d
IFLAGS		= -I$(INCDIR) -I$(LIBFTDIR)/include -I$(FONT_RENDIR)/include -I$(MLXDIR) -I$(MLXWDIR)/include
LFLAGS		= -L$(MLXDIR) -L$(MLXWDIR) -L$(LIBFTDIR) -L$(FONT_RENDIR) \
			  -lXext -lX11 -lXrandr -lm -lmlx -lmlx-wrapper -lfont-renderer -lft
OFLAGS		= -Ofast -ffast-math -funroll-loops -march=native -mtune=native
FFLAGS		= $(OFLAGS) -flto
CF			= $(CC) $(CFLAGS) $(IFLAGS)

# SRCS
include $(SRCDIR)/srcs.mk

ifeq ($(FULLSCREEN), 0) #potentiellement a remettre
endif
	SRCS += $(MLXDIR)/mlx_ext_randr.c
	CFLAGS += -Wno-error=sign-compare -Wno-error=return-type
	vpath %.c $(MLXDIR)

OBJS		= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
DEPS		= $(addprefix $(DEPDIR)/, $(notdir $(SRCS:.c=.o)))

# VPATH
vpath %.h $(INCDIR) $(LIBFTDIR)/$(INCDIR) $(MLXWDIR)/$(INCDIR) $(MLXDIR)
vpath %.o $(OBJDIR) $(LIBFTDIR)/$(OBJDIR) $(MLXWDIR)/$(OBJDIR)
vpath %.d $(DEPDIR) $(LIBFTDIR)/$(DEPDIR) $(MLXWDIR)/$(DEPDIR)

all: $(NAME)

debug: $(NAME)

fast: CFLAGS += $(FFLAGS)
fast: $(NAME)

$(NAME): $(FONT_RENDER) $(OBJS)
	$(call bin-link-msg)
	@$(CF) $^ $(LFLAGS) -o $@ $(FONT_RENDER) $(MLXW) $(MLX) $(LIBFT)
	$(call bin-finish-msg)

$(FONT_RENDER): $(MLXW) $(MLX) $(LIBFT)
	@$(MAKE) -s -C $(FONT_RENDIR) $(if $(filter 1,$(DEBUG)),debug) $(if $(filter 1,$(FAST)),CC="$(CC) $(FFLAGS)")

$(MLXW): $(MLX) $(LIBFT)
	@$(MAKE) -s -C $(MLXWDIR) $(if $(filter 1,$(DEBUG)),debug) $(if $(filter 1,$(FAST)),CC="$(CC) $(FFLAGS)")

$(LIBFT):
	@$(MAKE) -s -C $(LIBFTDIR) $(if $(filter 1,$(DEBUG)),debug) $(if $(filter 1,$(FAST)),CC="$(CC) $(FFLAGS)")

$(MLX):
	$(call mlx-build-msg)
	@$(MAKE) -s -C $(MLXDIR) $(if $(filter 1,$(FAST)),CC="gcc $(OFLAGS)") $(MUTE)
	$(call mlx-finish-msg)

$(OBJDIR)/%.o: %.c | buildmsg $(OBJDIR) $(DEPDIR)
	$(call bin-compile-obj-msg)
	@$(CF) $(DFLAGS) -c $< -o $@

$(OBJDIR) $(DEPDIR):
	$(call color,$(CYAN),"Creating directory %UL%$@")
	@mkdir -p $@

buildmsg:
ifneq ($(shell [ -f $(NAME) ] && echo exists),exists)
	$(call bin-build-msg)
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
	@$(MAKE) -s -C $(FONT_RENDIR) clean
	$(call rm-obj-msg)
	@rm -rf $(OBJDIR) $(DEPDIR)

fclean:
	@$(MAKE) -s -C $(FONT_RENDIR) fclean
	$(call rm-obj-msg)
	@rm -rf $(OBJDIR) $(DEPDIR)
	$(call rm-bin-msg)
	@rm -f $(NAME)

re: fclean all

refast: fclean fast

bonus: all

-include $(DEPS)

.PHONY: all debug fast refast re clean fclean help buildmsg print-%
