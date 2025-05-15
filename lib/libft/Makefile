NAME = libft.a

SRCDIR = src
OBJDIR = .obj
INCDIR = include

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
       ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
       ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
       ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
       ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
       ft_striteri.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
       ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
       ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
       ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
       ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c free_tab.c \
       ft_strndup.c ft_strcmp.c ft_str_is_digit.c ft_swap_int.c ft_max.c \
       vector_add.c vector_init.c ft_tab_len.c ft_getintlen.c is_above_int.c \
       get_vector_value.c ft_abs.c ft_gap.c ft_min.c ft_strsjoin.c \
       get_next_line.c av.c ft_fabs.c ft_swap_float.c free_vector.c \
       ft_strtok.c

OBJS = $(addprefix $(OBJDIR)/,$(SRCS:.c=.o))

CFLAGS = -Werror -Wextra -Wall -MD -MP -I $(INCDIR) -g -Ofast
AR = ar -rcs
DEPFLAGS = -MMD -MP

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean
	make all

-include $(OBJS:.o=.d)

.PHONY: all clean fclean re
