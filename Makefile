# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 17:43:39 by jaubry--          #+#    #+#              #
#    Updated: 2026/01/19 20:18:56 by jaubry--         ###   ########.fr        #
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

INCXTEST	= $(LIBDIR)/local_xtst/include/X11/extensions

INCLUDES	= $(INCDIRS_MINIRT) \
			  $(addprefix $(XCERRCALDIR)/, $(INCDIRS_XCERRCAL)) \
			  $(addprefix $(FONT_RENDIR)/, $(INCDIRS_FTRDR)) \
			  $(addprefix $(MLXWDIR)/, $(INCDIRS_MLXW)) \
			  $(addprefix $(MLXUIDIR)/, $(INCDIRS_MLXUI)) \
			  $(addprefix $(LIBFTDIR)/, $(INCDIRS_LIBFT)) \
			  $(MLXDIR)


# Output
NAME		= MiniRT
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
WIDTH		= 500
HEIGHT		= 500
endif

PERF		= 0

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
			  CL_TARGET_OPENCL_VERSION=300

# Compiler and flags
CC			?= cc

CFLAGS		= -Wall -Werror -Wextra \
			  -std=gnu11

DFLAGS		= -MMD -MP -MF $(DEPDIR)/$*.d

IFLAGS		= $(addprefix -I,$(INCLUDES) $(INCXTEST))

LXTEST		= $(LIBDIR)/local_xtst/lib
LFLAGS		= -L$(FONT_RENDIR) -L$(MLXWDIR) -L$(LIBFTDIR) -L$(MLXDIR) -L$(XCERRCALDIR) -L$(LXTEST) \
			  -lfont-renderer -lmlx-wrapper -lmlx -lft -lxcerrcal \
			  -lXtst -lXext -lX11 -lXrandr -lm -l:libOpenCL.so.1

# i think it is the same as putting -lOpenCL == -l:libOpenCL.so.1

VFLAGS		= $(addprefix -D ,$(VARS) DEBUG=$(DEBUG))

CFLAGS		+= $(INSPECT_FLAGS) $(PROFILE_FLAGS) $(FFLAGS) $(VFLAGS)

CF			= $(CC) $(CFLAGS) $(IFLAGS)

# Sources
include $(SRCDIR)/srcs.mk

OBJS		= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
DEPS		= $(addprefix $(DEPDIR)/, $(notdir $(SRCS:.c=.o)))

# VPATH
vpath %.h $(INCLUDES)
vpath %.o $(OBJDIR) $(LIBFTDIR)/$(OBJDIR) $(MLXWDIR)/$(OBJDIR)
vpath %.d $(DEPDIR) $(LIBFTDIR)/$(DEPDIR) $(MLXWDIR)/$(DEPDIR)

all:	$(NAME)
fast:	$(NAME)
debug:	$(NAME)

$(NAME): $(XCERRCAL) $(MLXUI) $(FONT_RENDER) $(OBJS) $(INCLUDES)
	$(call bin-link-msg)
	$(CF) $(OBJS) $(ARCHIVES) $(LFLAGS) -o $@
	$(call bin-finish-msg)

$(XCERRCAL):
	@$(MAKE) -s -C $(XCERRCALDIR) $(RULE) $(VARS) ROOTDIR=../..

$(MLXUI): $(FONT_RENDER) $(MLXW) $(MLX) $(LIBFT)
	@$(MAKE) -s -C $(MLXUIDIR) $(RULE)  $(VARS) ROOTDIR=../..

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
	@echo "╔══════════════════════════════════════════════════════════╗"
	@echo "║             miniRT — Build System Help                  ║"
	@echo "╚══════════════════════════════════════════════════════════╝"
	@echo ""
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo "  AVAILABLE TARGETS"
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo ""
	@echo "  Standard Builds:"
	@echo "    all                    Build $(NAME) (default, no optimization)"
	@echo "    fast                   Build $(NAME) with -Ofast -march=native"
	@echo "    debug                  Build $(NAME) with DEBUG_LVL=1 (debug symbols)"
	@echo "    inspect                Build with -g3 for LLDB/gdb debugging"
	@echo "    profile                Build with -g3 -pg for gprof profiling"
	@echo ""
	@echo "  Sanitizer Builds:"
	@echo "    san-mem                AddressSanitizer (heap/stack/global OOB, UAF)"
	@echo "    san-leak               LeakSanitizer (memory leak detection + ASan)"
	@echo "    san-ub                 Undefined Behavior Sanitizer (all UB checks)"
	@echo ""
	@echo "  Rebuilds (fclean + build):"
	@echo "    re                     fclean + all"
	@echo "    refast                 fclean + fast"
	@echo "    redebug                fclean + debug"
	@echo "    reinspect              fclean + inspect"
	@echo "    reprofile              fclean + profile"
	@echo "    resan-mem              fclean + san-mem"
	@echo "    resan-leak             fclean + san-leak"
	@echo "    resan-ub               fclean + san-ub"
	@echo ""
	@echo "  Maintenance:"
	@echo "    clean                  Remove object and dependency files"
	@echo "    fclean                 clean + remove libraries and $(NAME) binary"
	@echo "    help                   Show this help message"
	@echo "    bonus                  Same as all (42 School requirement)"
	@echo "    print-%                Print value of Makefile variable %"
	@echo ""
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo "  SUBMODULE BUILD CHAIN & DEPENDENCY ORDER"
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo ""
	@echo "    minilibx-linux (MLX)       — X11 window / image library"
	@echo "        ↑"
	@echo "    libft (LIBFT)               — 42 standard library"
	@echo "        ↑"
	@echo "    mlx_wrapper (MLXW)          — MLX convenience wrapper"
	@echo "        ↑"
	@echo "    font_renderer (FONT_RENDER) — TrueType text rendering on MLX"
	@echo "        ↑"
	@echo "    mlxui (MLXUI)               — UI toolkit over MLX"
	@echo "        ↑"
	@echo "    xcerrcal (XCERRCAL)         — Error handling library (independent)"
	@echo ""
	@echo "    Build order: MLX -> LIBFT -> MLXW -> FONT_RENDER -> MLXUI -> XCERRCAL"
	@echo ""
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo "  BUILD FLAGS"
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo ""
	@echo "    Flag                     Default   Description"
	@echo "    ─────────────────────────────────────────────────────"
	@echo "    WIDTH                    500       Window width (or MAX_WIDTH)"
	@echo "    HEIGHT                   500       Window height (or MAX_HEIGHT)"
	@echo "    FULLSCREEN               0         Use screen resolution"
	@echo "    RESIZEABLE               0         Enable window resize"
	@echo "    WINDOWLESS               0         Headless mode (no window)"
	@echo "    PERF                     0         Performance mode"
	@echo "    NPROC                    $(nproc)  Parallel job count"
	@echo "    VERBOSE                  0         Show compile commands"
	@echo "    CL_TARGET_OPENCL_VERSION 300       OpenCL target version"
	@echo "    DEBUG_LVL                0         Tiered debug (1=all submodules, 5=+miniRT)"
	@echo "                                      1=all, 2=+mlx_wrapper, 3=+font_renderer,"
	@echo "                                      4=+mlxui, 5=+miniRT binary"
	@echo "    FAST                     auto      -Ofast -march=native -mtune=native -msse3"
	@echo ""
	@echo "    Usage: make WIDTH=1920 HEIGHT=1080 FULLSCREEN=1"
	@echo ""
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo "  SANITIZER RUNTIME ENVIRONMENT VARIABLES"
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo ""
	@echo "  Export these before running a sanitizer build:"
	@echo ""
	@echo "  san-mem (AddressSanitizer):"
	@echo "    export ASAN_OPTIONS=\"intercept_tls_get_addr=0:detect_leaks=0:\\"
	@echo "      quarantine_size_mb=512:redzone=128:max_redzone=2048:\\"
	@echo "      report_globals=1:check_initialization_order=1:\\"
	@echo "      strict_init_order=1:detect_stack_use_after_return=0:\\"
	@echo "      min_uar_stack_size_log=16:max_uar_stack_size_log=20:\\"
	@echo "      detect_container_overflow=1:detect_odr_violation=2:\\"
	@echo "      strict_string_checks=1:replace_str=1:replace_intrin=1:\\"
	@echo "      print_stats=1:print_legend=1:atexit=1:\\"
	@echo "      print_full_thread_history=1:alloc_dealloc_mismatch=1:\\"
	@echo "      new_delete_type_mismatch=1:poison_heap=1:poison_partial=1:\\"
	@echo "      poison_array_cookie=1:max_malloc_fill_size=8192:\\"
	@echo "      allow_user_poisoning=1:check_malloc_usable_size=1:\\"
	@echo "      sleep_before_dying=0:verbosity=1:halt_on_error=0:\\"
	@echo "      dump_instruction_bytes=1:protect_shadow_gap=0:\\"
	@echo "      interceptor_via_fun=0\""
	@echo ""
	@echo "  san-leak (LeakSanitizer):"
	@echo "    export LSAN_OPTIONS=\"verbosity=1:log_threads=0:log_pointers=0:\\"
	@echo "      report_objects=0:use_registers=1:use_globals=1:use_stacks=1:\\"
	@echo "      use_root_regions=1:use_ld_allocations=1:use_tls=1:\\"
	@echo "      use_unaligned=1:print_suppressions=0:max_leaks=0:exitcode=23\""
	@echo "    export ASAN_OPTIONS=\"detect_leaks=1:leak_check_at_exit=1:\\"
	@echo "      malloc_context_size=50:print_full_thread_history=1:verbosity=1\""
	@echo ""
	@echo "  san-ub (Undefined Behavior Sanitizer):"
	@echo "    export UBSAN_OPTIONS=\"print_stacktrace=1:halt_on_error=0:\\"
	@echo "      verbosity=1:report_error_type=1\""
	@echo ""
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo "  USAGE EXAMPLES"
	@echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	@echo ""
	@echo "    make                          # default build"
	@echo "    make fast                     # optimized build"
	@echo "    make WIDTH=800 HEIGHT=600     # custom resolution"
	@echo "    make debug                    # debug symbols"
	@echo "    make inspect                  # LLDB/gdb (-g3)"
	@echo "    make profile                  # gprof profiling"
	@echo ""
	@echo "    # Sanitizer builds (export env vars first, see above)"
	@echo "    export ASAN_OPTIONS=\"...\""
	@echo "    make san-mem && ./MiniRT asset/scenes/template.rt"
	@echo ""
	@echo "    export LSAN_OPTIONS=\"...\""
	@echo "    export ASAN_OPTIONS=\"...\""
	@echo "    make san-leak && ./MiniRT asset/scenes/template.rt"
	@echo ""
	@echo "    export UBSAN_OPTIONS=\"...\""
	@echo "    make san-ub && ./MiniRT asset/scenes/template.rt"
	@echo ""
	@echo "    make re                       # rebuild from scratch"
	@echo "    make refast                   # rebuild optimized from scratch"
	@echo "    make clean                    # remove objects only"
	@echo "    make fclean                   # remove everything and start over"

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
