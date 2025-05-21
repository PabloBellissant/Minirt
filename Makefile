NAME = Minirt

SRCDIR = src
OBJDIR = obj
INCDIR = include
LIBFTDIR = lib/libft
LIBFTINC = $(LIBFTDIR)/include
MLX_DIR = lib/minilibx-linux

SRCS =	$(addprefix $(SRCDIR)/, \
		parsing/glb_parser/glb_parser.c \
		parsing/glb_parser/data/get_object_data.c \
		parsing/json_parser/json_parser.c \
		parsing/json_parser/recursive_parse.c \
		parsing/json_parser/extract_len.c \
		parsing/json_parser/fill_json_data.c \
		parsing/json_parser/get_end_brackets.c \
		parsing/json_parser/get_next_data.c \
		parsing/json_parser/get_type.c \
		parsing/json_parser/fill_array.c \
		parsing/map/parse_map.c \
		init/init_graphics.c \
		main.c)

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

LIBFT = $(LIBFTDIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

CFLAGS = -Wall -Wextra -Werror -I $(INCDIR) -I $(LIBFTINC) -I $(MLX_DIR) -g
LDFLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm -lz
DEPFLAGS = -MMD -MP
MAKEFLAGS = --no-print-directory


all: $(NAME)

fast: CFLAGS += -Ofast
fast: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

$(LIBFT): FORCE
	$(MAKE) -C $(LIBFTDIR)

$(MLX): FORCE
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -rf $(OBJDIR)
	$(MAKE) clean -C $(LIBFTDIR)
	$(MAKE) clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR)

re: fclean
	make all

refast: fclean
	make fast

bonus: all

debug: $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -pg -o $@ $^ $(LDFLAGS)

-include $(DEPS)

.PHONY: all clean fclean re bonus FORCE
