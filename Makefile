# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 17:43:39 by jaubry--          #+#    #+#              #
#    Updated: 2026/02/20 18:38:59 by jaubry--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ROOTDIR		= .
include $(ROOTDIR)/mkidir/make_utils.mk

# Directories
SRCDIR		= src
INCDIR		= include
OBJDIR		= .obj
DEPDIR		= .dep

XCERRCALDIR	= $(LIBDIR)/xcerrcal
LIBFTDIR	= $(LIBDIR)/libft
MLXDIR		= $(LIBDIR)/minilibx-linux
MLXWDIR		= $(LIBDIR)/mlx_wrapper
FONT_RENDIR	= $(LIBDIR)/font_renderer
MLXUIDIR	= $(LIBDIR)/mlxui

# Includes
include $(LIBFTDIR)/includes.mk $(XCERRCALDIR)/includes.mk \
	$(MLXWDIR)/includes.mk $(FONT_RENDIR)/includes.mk \
	$(MLXUIDIR)/includes.mk includes.mk

INCLUDES	= $(INCDIRS_MINIRT) \
			  $(addprefix $(XCERRCALDIR)/, $(INCDIRS_XCERRCAL)) \
			  $(addprefix $(FONT_RENDIR)/, $(INCDIRS_FTRDR)) \
			  $(addprefix $(MLXWDIR)/, $(INCDIRS_MLXW)) \
			  $(addprefix $(MLXUIDIR)/, $(INCDIRS_MLXUI)) \
			  $(addprefix $(LIBFTDIR)/, $(INCDIRS_LIBFT)) \
			  $(MLXDIR)


# Output
NAME		= miniRT
XCERRCAL	= $(XCERRCALDIR)/libxcerrcal.a
LIBFT		= $(LIBFTDIR)/libft.a
MLX			= $(MLXDIR)/libmlx.a
MLXW		= $(MLXWDIR)/libmlx-wrapper.a
FONT_RENDER	= $(FONT_RENDIR)/libfont-renderer.a
MLXUI		= $(MLXUIDIR)/libmlxui.a
ARCHIVES	= $(MLXUI) $(FONT_RENDER) $(MLXW) $(MLX) $(LIBFT) $(XCERRCAL)

# Variables
DEBUG_MINIRT = 5

ifeq ($(filter $(DEBUG_LVL),1 $(DEBUG_MINIRT)),)
DEBUG		= 0
else
DEBUG		= 1
endif

WINDOWLESS	= 0
FULLSCREEN	= 0
RESIZEABLE	= 0

ifeq ($(FULLSCREEN), 1)
WIDTH		= $(MAX_WIDTH)
HEIGHT		= $(MAX_HEIGHT)
else
WIDTH		= 1920
HEIGHT		= 1080
endif

PERF		= 0
MINIRT_MODE	= 1
CL_TARGET_OPENCL_VERSION=300

VARS		= DEBUG_LVL=$(DEBUG_LVL) \
			  MAX_WIDTH=$(MAX_WIDTH) \
			  MAX_HEIGHT=$(MAX_HEIGHT) \
			  WIDTH=$(WIDTH) \
			  HEIGHT=$(HEIGHT) \
			  PERF=$(PERF) \
			  FULLSCREEN=$(FULLSCREEN) \
			  RESIZEABLE=$(RESIZEABLE) \
			  WINDOWLESS=$(WINDOWLESS) \
			  NPROC=$(NPROC) \
			  MINIRT_MODE=$(MINIRT_MODE) \
			  CL_TARGET_OPENCL_VERSION=$(CL_TARGET_OPENCL_VERSION)

# Compiler and flags
CC			?= cc

CFLAGS		= -Wall -Werror -Wextra \
			  -std=gnu11

DFLAGS		= -MMD -MP -MF $(DEPDIR)/$*.d

IFLAGS		= $(addprefix -I,$(INCLUDES) $(INCXTEST))

LXTEST		= $(MLXDIR)/local_xtst/lib
LFLAGS		= -L$(FONT_RENDIR) -L$(MLXWDIR) -L$(LIBFTDIR) -L$(MLXDIR) -L$(XCERRCALDIR) \
			  -lfont-renderer -lmlx-wrapper -lmlx -lft -lxcerrcal \
			  -lXtst -lXext -lX11 -lXrandr -lm -l:libOpenCL.so.1

VFLAGS		= $(addprefix -D ,$(VARS) DEBUG=$(DEBUG))

CFLAGS		+= $(SANITIZE_FLAGS) $(INSPECT_FLAGS) $(PROFILE_FLAGS) $(FFLAGS) $(VFLAGS)

CF			= $(CC) $(CFLAGS) $(IFLAGS)

# Sources
include $(SRCDIR)/srcs.mk

OBJS		= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
DEPS		= $(addprefix $(DEPDIR)/, $(notdir $(SRCS:.c=.o)))

# VPATH
vpath %.h $(INCLUDES)
vpath %.o $(OBJDIR) $(LIBFTDIR)/$(OBJDIR) $(MLXWDIR)/$(OBJDIR)
vpath %.d $(DEPDIR) $(LIBFTDIR)/$(DEPDIR) $(MLXWDIR)/$(DEPDIR)

bonus: $(NAME)

include $(ROOTDIR)/mkidir/make_rules.mk

$(NAME): $(XCERRCAL) $(MLXUI) $(FONT_RENDER) $(OBJS) $(INCLUDES)
	$(call bin-link-msg)
ifeq ($(VERBOSE),1)
	$(CF) $(OBJS) $(ARCHIVES) $(LFLAGS) -o $@
else
	@$(CF) $(OBJS) $(ARCHIVES) $(LFLAGS) -o $@
endif
	$(call bin-finish-msg)

$(XCERRCAL):
ifeq ($(VERBOSE),1)
	$(MAKE) -C $(XCERRCALDIR) $(RULE) $(VARS) ROOTDIR=../..
else
	@$(MAKE) -s -C $(XCERRCALDIR) $(RULE) $(VARS) ROOTDIR=../..
endif

$(MLXUI): $(FONT_RENDER) $(MLXW) $(MLX) $(LIBFT)
ifeq ($(VERBOSE),1)
	$(MAKE) -C $(MLXUIDIR) $(RULE) $(VARS) ROOTDIR=../..
else
	@$(MAKE) -s -C $(MLXUIDIR) $(RULE) $(VARS) ROOTDIR=../..
endif

$(FONT_RENDER): $(MLXW) $(MLX) $(LIBFT)
ifeq ($(VERBOSE),1)
	$(MAKE) -C $(FONT_RENDIR) $(RULE) $(VARS) ROOTDIR=../..
else
	@$(MAKE) -s -C $(FONT_RENDIR) $(RULE) $(VARS) ROOTDIR=../..
endif

$(MLXW): $(MLX) $(LIBFT)
ifeq ($(VERBOSE),1)
	$(MAKE) -C $(MLXWDIR) $(RULE) $(VARS) ROOTDIR=../..
else
	@$(MAKE) -s -C $(MLXWDIR) $(RULE) $(VARS) ROOTDIR=../..
endif

$(LIBFT):
ifeq ($(VERBOSE),1)
	$(MAKE) -C $(LIBFTDIR) $(RULE) $(VARS) ROOTDIR=../..
else
	@$(MAKE) -s -C $(LIBFTDIR) $(RULE) $(VARS) ROOTDIR=../..
endif

$(MLX):
	$(call mlx-build-msg)
	@$(MAKE) -s -C $(MLXDIR) CC="$(MLX_GCC) $(if $(filter 1,$(FAST)),$(OFLAGS))" $(MUTE)
	$(call mlx-finish-msg)

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

clean:
	@$(MAKE) -s -C $(MLXUIDIR) clean ROOTDIR=../..
	$(call rm-obj-msg)
	@rm -rf $(OBJDIR) $(DEPDIR)

fclean:
	@$(MAKE) -s -C $(MLXUIDIR) fclean ROOTDIR=../..
	$(call rm-obj-msg)
	@rm -rf $(OBJDIR) $(DEPDIR)
	$(call rm-bin-msg)
	@rm -f $(NAME)


-include $(DEPS)

.PHONY: all bonus clean fclean
.PHONY: help buildmsg
