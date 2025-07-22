/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaubry-- <jaubry--@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 07:36:56 by jaubry--          #+#    #+#             */
/*   Updated: 2025/07/23 00:54:55 by jaubry--         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdarg.h>
# include <stdint.h>

# define VECTOR_BASE_SIZE 128

/* -------------------------------------------------------------------------- */
/*                                 Conversions                                */
/* -------------------------------------------------------------------------- */

/* -------------------------- Type conversion utils ------------------------- */
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
float	ft_atod(const char *str);
int		ratoi(const char *str);
bool	check_flow(char *str, int ret);

/* ------------------------- Char conversions utils ------------------------- */
int		ft_tolower(int c);
int		ft_toupper(int c);

//
//
//

/* -------------------------------------------------------------------------- */
/*                                Parsing utils                               */
/* -------------------------------------------------------------------------- */

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
bool	ft_isspace(const char c);

bool	is_in(const char *str, char c);
bool	has_in(const char *str, bool is_char(char));
int		count_tokens(const char *str, char sep);

//
//
//

/* -------------------------------------------------------------------------- */
/*                                Memory utils                                */
/* -------------------------------------------------------------------------- */

void	ft_bzero(void *s, size_t n);
void	*ft_fbzero(void *s, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);

//
//
//

/* -------------------------------------------------------------------------- */
/*                                String utils                                */
/* -------------------------------------------------------------------------- */

size_t	ft_strlen(const char *str);

char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strcrop(const char *str, int c);

char	*ft_strrchr(const char *s, int c);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strdup(const char *src);
char	*ft_strndup(const char *str, size_t n);

int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strstr(const char *big, const char *little);
char	*ft_strnstr(const char *big, const char *little, size_t len);

size_t	ft_strlcat(char *dst, char const *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char	*ft_strjoin(char const *s1, char const *s2);
char	*freejoin(char *s1, const char *s2);
char	*dfreejoin(char *s1, char *s2);
char	*ft_strjoin_all(size_t	str_nb, ...);

//
//
//

/* -------------------------------------------------------------------------- */
/*                             String arrays utils                            */
/* -------------------------------------------------------------------------- */

char	**ft_split(const char *str, int c);
char	**split_by_char(const char *str, bool is_char(char));
char	**ft_strrdup(char **strs);
size_t	ft_strrlen(char **strs);
void	free_strr(char **strs);
void	free_strr_fail(char **strs, size_t size);
int		strr_add(char ***strs, char *str);

//
//
//

/* -------------------------------------------------------------------------- */
/*                              Allocation utils                              */
/* -------------------------------------------------------------------------- */

void	ft_free(void *pnt);
void	*ft_calloc(size_t len, size_t size);
void	*ft_realloc(void *pnt, size_t old_size, size_t size);

//
//
//

/* -------------------------------------------------------------------------- */
/*                                  IO utils                                  */
/* -------------------------------------------------------------------------- */

/* --------------------------------- Output --------------------------------- */
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_printf(const char *format, ...);
int		ft_dprintf(int fd, const char *format, ...);
int		ft_vdprintf(int fd, const char *format, va_list ap);

/* ---------------------------------- Input --------------------------------- */
char	*get_next_line(int fd);
typedef struct s_limits
{
	int	min;
	int	max;
}	t_limits;

typedef union u_result
{
	float	*float_t;
	int		*int_t;
	uint8_t	*uint8_t;
}	t_result;
int		ft_scan(int line_num, char *format, char *line, ...);
//
//
//

/* -------------------------------------------------------------------------- */
/*                               Data structures                              */
/* -------------------------------------------------------------------------- */

/* ------------------------------ Chained list ------------------------------ */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);

int		ft_lstsize(t_list *lst);

t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstgetindex(t_list *lst, size_t index);

void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstadd_after(t_list **lst, t_list *new);

void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstpop(t_list **lst, t_list **el, void (*del)(void *));

void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* --------------------------- Double chained list -------------------------- */
typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

t_dlist	*ft_dlstnew(void *content);

int		ft_dlstsize(t_dlist *lst);

t_dlist	*ft_dlstfirst(t_dlist *lst);
t_dlist	*ft_dlstlast(t_dlist *lst);

void	ft_dlstadd_front(t_dlist **alst, t_dlist *new);
void	ft_dlstadd_back(t_dlist **alst, t_dlist *new);

void	ft_dlstdelone(t_dlist *lst, void (*del)(void *));
void	ft_dlstclear(t_dlist **lst, void (*del)(void *));

void	ft_dlstiter(t_dlist *lst, void (*f)(void *));
t_dlist	*ft_dlstmap(t_dlist *lst, void *(*f)(void *), void (*del)(void *));

int		ft_dlstindex(t_dlist *lst, t_dlist *to_find);
t_dlist	*ft_dlstget_index(t_dlist *lst, size_t index);

t_dlist	*ft_dlstdup(const t_dlist *lst, void (*del)(void*));

void	ft_dlstswap(t_dlist *l1, t_dlist *l2);

/* -------------------------------- Vector ---------------------------------- */
typedef struct s_vector
{
	size_t	element_size;
	size_t	num_elements;
	size_t	max_elements;
	void	*data;
}			t_vector;

void	vector_init(t_vector *vector, size_t element_size);
int		vector_add(t_vector *vector, void *element, size_t elem_count);

void	*get_vector_value(t_vector *vector, size_t i);

void	free_vector(t_vector *vector);
int		vector_realloc(t_vector *vector);

int		set_vector_size(t_vector *vector, size_t size);

void	remove_vector_elem(t_vector *vector, size_t i);

#endif
