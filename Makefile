# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 17:43:39 by jaubry--          #+#    #+#              #
#    Updated: 2025/09/09 01:46:35 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOTDIR		= .
include $(ROOTDIR)/mkidir/make_utils.mk

# Variables
NPROC		= $(shell nproc)
WINDOWLESS	= 0
FULLSCREEN	= 0
RESIZEABLE	= 0
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
ARCHIVES	= $(FONT_RENDER) $(MLXW) $(MLX) $(LIBFT)

# Compiler and flags
CC			= cc

CFLAGS		= -Wall -Werror -Wextra \
			  -std=gnu11

DFLAGS		= -MMD -MP -MF $(DEPDIR)/$*.d

IFLAGS		= -I$(INCDIR) -I$(FONT_RENDIR)/include -I$(MLXWDIR)/include \
			  -I$(LIBFTDIR)/include -I$(MLXDIR)

LFLAGS		= -L$(FONT_RENDIR) -L$(MLXWDIR) -L$(LIBFTDIR) -L$(MLXDIR) \
			  -lfont-renderer -lmlx-wrapper -lmlx -lft \
			  -lXext -lX11 -lXrandr -lm

VARS		= DEBUG=$(DEBUG) \
			  WIDTH=$(WIDTH) \
			  HEIGHT=$(HEIGHT) \
			  PERF=$(PERF) \
			  FULLSCREEN=$(FULLSCREEN) \
			  RESIZEABLE=$(RESIZEABLE) \
			  WINDOWLESS=$(WINDOWLESS) \
			  NPROC=$(NPROC)
VFLAGS		= $(addprefix -D ,$(VARS))

CFLAGS		+= $(DEBUG_FLAGS) $(FFLAGS) $(VFLAGS)

CF			= $(CC) $(CFLAGS) $(IFLAGS)

# SRCS
include $(SRCDIR)/srcs.mk

OBJS		= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
DEPS		= $(addprefix $(DEPDIR)/, $(notdir $(SRCS:.c=.o)))
INCLUDES	= bvh.h calc.h minirt.h object.h parsing.h render.h
INCLUDES	:= $(addprefix $(INCDIR)/, $(INCLUDES))

# VPATH
vpath %.h $(INCDIR) $(LIBFTDIR)/$(INCDIR) $(MLXWDIR)/$(INCDIR) $(MLXDIR)
vpath %.o $(OBJDIR) $(LIBFTDIR)/$(OBJDIR) $(MLXWDIR)/$(OBJDIR)
vpath %.d $(DEPDIR) $(LIBFTDIR)/$(DEPDIR) $(MLXWDIR)/$(DEPDIR)

all:	$(NAME)
fast:	$(NAME)
debug:	$(NAME)

$(NAME): $(FONT_RENDER) $(OBJS) $(INCLUDES)
	$(call bin-link-msg)
	@$(CF) $(OBJS) $(ARCHIVES) $(LFLAGS) -o $@
	$(call bin-finish-msg)

$(FONT_RENDER): $(MLXW) $(MLX) $(LIBFT)
	@$(MAKE) -s -C $(FONT_RENDIR) $(RULE)  $(VARS) ROOTDIR=../..

$(MLXW): $(MLX) $(LIBFT)
	@$(MAKE) -s -C $(MLXWDIR) $(RULE)  $(VARS) ROOTDIR=../..

$(LIBFT):
	@$(MAKE) -s -C $(LIBFTDIR) $(RULE)  $(VARS) ROOTDIR=../..

$(MLX):
	$(call mlx-build-msg)
	@$(MAKE) -s -C $(MLXDIR) CC="$(MLX_GCC) $(if $(filter 1,$(FAST)),$(OFLAGS))" $(MUTE)
	$(call mlx-finish-msg)

$(OBJDIR)/%.o: %.c $(INCLUDES) | buildmsg $(OBJDIR) $(DEPDIR)
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
	@$(MAKE) -s -C $(FONT_RENDIR) clean ROOTDIR=../..
	$(call rm-obj-msg)
	@rm -rf $(OBJDIR) $(DEPDIR)

fclean:
	@$(MAKE) -s -C $(FONT_RENDIR) fclean ROOTDIR=../..
	$(call rm-obj-msg)
	@rm -rf $(OBJDIR) $(DEPDIR)
	$(call rm-bin-msg)
	@rm -f $(NAME)

re: 	fclean all
refast:	fclean fast
redebug:fclean debug

bonus: all

-include $(DEPS)

.PHONY: all debug fast refast redebug re clean fclean help buildmsg print-%
