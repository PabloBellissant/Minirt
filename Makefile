NAME = Minirt

SRCDIR = src
OBJDIR = obj
INCDIR = include
LIBFTDIR = lib/libft
LIBFTINC = $(LIBFTDIR)/include
MLX_DIR = lib/better_mlx

SRCS =	$(addprefix $(SRCDIR)/, \
		parsing/glb_parser/glb_parser.c \
		parsing/glb_parser/data/get_object_data.c \
		parsing/glb_parser/data/get_scene_name.c \
		parsing/glb_parser/data/get_object_count.c \
		parsing/glb_parser/data/get_vertex_count.c \
		parsing/glb_parser/data/get_mesh_id.c \
		parsing/glb_parser/data/get_pos_accessors.c \
		parsing/glb_parser/data/get_vertex.c \
		parsing/glb_parser/parse_objects.c \
		parsing/json_parser/json_parser.c \
		parsing/json_parser/recursive_parse.c \
		parsing/json_parser/extract_len.c \
		parsing/json_parser/fill_json_data.c \
		parsing/json_parser/get_end_brackets.c \
		parsing/json_parser/get_next_data.c \
		parsing/json_parser/get_json_type.c \
		parsing/json_parser/fill_array.c \
		parsing/json_parser/get_by_key_name.c \
		parsing/json_parser/fix_json_str.c \
		parsing/map/parse_map.c \
		parsing/rt_parser/rt_parser.c \
		parsing/rt_parser/parse_line.c \
		parsing/rt_parser/get_type.c \
		parsing/rt_parser/check_double.c \
		parsing/rt_parser/type/create_object.c \
		parsing/rt_parser/type/ambient.c \
		parsing/rt_parser/type/camera.c \
		parsing/rt_parser/type/light.c \
		parsing/rt_parser/type/sphere.c \
		parsing/rt_parser/type/plane.c \
		parsing/rt_parser/type/cylinder.c \
		parsing/obj_parser/obj_parser.c \
		init/init_graphics.c \
		draw/put_pixel.c \
		draw/draw_line.c \
		draw/draw_bvh.c \
		draw/rasterization.c \
		loop_hook.c \
		loop.c \
		calc/ray_path.c \
		calc/hit_register.c \
		calc/objects/hit_plane.c \
		calc/objects/hit_sphere.c \
		calc/objects/hit_triangle.c \
		calc/objects/hit_cylinder.c \
		calc/bvh/hit_bvh.c \
		calc/bvh/get_bvh_area.c \
		calc/bvh/get_next_bvh_area.c \
		calc/bvh/create_bvh.c \
		calc/bvh/merge_bvh.c \
		calc/bvh/merge_nearest_bvh.c \
		multi_threading/init_threads.c \
		multi_threading/routine.c \
		multi_threading/task_stack/enqueue.c \
		multi_threading/task_stack/dequeue.c \
		multi_threading/kill_threads.c \
		vec3/vec3_add.c \
		vec3/vec3_sub.c \
		vec3/vec3_scale.c \
		vec3/vec3_add_scalar.c \
		vec3/vec3_div_scalar.c \
		vec3/vec3_length.c \
		vec3/vec3_length_squared.c \
		vec3/vec3_unit.c \
		vec3/vec3_dot.c \
		vec3/vec3_lerp.c \
		vec3/vec3_cross.c \
		vec3/vec3_random.c \
		clear_scene.c \
		main.c)

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
DEPS = $(OBJS:.o=.d)

LIBFT = $(LIBFTDIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

CFLAGS = -Wall -Werror -Wextra -I $(INCDIR) -I $(LIBFTINC) -I $(MLX_DIR) -g -march=native -msse3 -Rpass-missed=.*
LDFLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm -lz -lXrandr
DEPFLAGS = -MMD -MP
MAKEFLAGS = --no-print-directory

all: $(NAME)

fast: CFLAGS += -Ofast -march=native -mtune=native -flto -funroll-loops
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
