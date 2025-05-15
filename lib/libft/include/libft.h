/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabellis <mail@bellissantpablo.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:26:50 by pabellis          #+#    #+#             */
/*   Updated: 2025/02/06 00:49:41 by pabellis         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdbool.h>
# include <stdio.h>

# define LOWER_UPPER_VAL 32

float	ft_fabs(float val);

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_str_is_digit(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_atoi(const char *nptr);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		free_tab(char **tab);
int		av(const int val_a, const int val_b);
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
int		ft_putnbr_fd(int n, int fd);

size_t	ft_strlen(const char *s);
size_t	ft_securestrlen(const char *s);
size_t	ft_tab_len(void **tab);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_getintlen(int n);
size_t	ft_abs(const ssize_t value);
size_t	ft_gap(const ssize_t value_a, const ssize_t value_b);

ssize_t	ft_max(const ssize_t val1, const ssize_t val2);
ssize_t	ft_min(const ssize_t val1, const ssize_t val2);

void	*ft_memset(void *s, int c, size_t n);
void	*ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putendl_fd(char *s, int fd);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	swap_int(int *val1, int *val2);
void	swap_float(float *val1, float *val2);

char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*secure_strjoin(char *s1, char *s2);
char	*ft_strjoinerr(char const *s1, char const *s2, ssize_t err);
char	*ft_strsjoin(char *first, ...);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*get_next_line(int fd);
char	*ft_strtok(char *s, const char *delim);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstadd_front(t_list **lst, t_list *new);

int		ft_lstsize(t_list *lst);

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)
			(void *), void (*del)(void *));

typedef struct s_vector
{
	size_t	element_size;
	size_t	num_elements;
	size_t	max_elements;
	void	*data;
}				t_vector;

int		vector_add(t_vector *vector, void *element);
int		vector_init(t_vector *vector, size_t element_size);
void	*get_vector_value(t_vector *vector, size_t i);
void	free_vector(t_vector *vector);
int		vector_realloc(t_vector *vector);

bool	is_above_int(char *value_in_str);

#endif
