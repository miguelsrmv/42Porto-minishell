/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 20:15:57 by mde-sa--          #+#    #+#             */
/*   Updated: 2024/03/29 12:39:49 by mde-sa--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include <stdbool.h>

/* Part 1: Libc functions */
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *str);
void	*ft_memset(void *dest, int c, size_t len);
void	ft_bzero(void *dest, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t n);
size_t	ft_strlcat(char *dest, const char *src, size_t n);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *s, const char *find, size_t n);
int		ft_atoi(const char *s);
void	*ft_calloc(size_t c, size_t n);
char	*ft_strdup(const char *src);

/* Part 2: Additional functions */
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/* Part 3: Libft bonus */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void*));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* Part 4: ft_printf */
int		ft_printf(const char *string, ...);
int		ft_printf_char_fd(char c, int fd);
int		ft_printf_string_fd(char *string, int fd);
int		ft_printf_pointer_fd(void *pointer, int fd);
int		ft_printf_int_fd(int integer, int fd);
int		ft_printf_unsint_fd(unsigned int unsigned_n, int fd);
int		ft_printf_base_fd(int integer, char *base, int fd);
int		ft_printf_ptr_fd(void *address, int fd);
int		ft_str_format(char *string);
char	*ft_utoa(unsigned int n);
char	*ft_itoa_base(unsigned int integer, char *base);
char	*ft_lutoa_base(long unsigned int address, char *base);
char	*ft_strrev(char *str);

/* Part 5: get_next_line */
size_t	ft_gnl_strlen(const char *str);
char	*get_next_line(int fd);
char	*ft_gnl_get_text(int fd, char *buffer);
char	*ft_gnl_strchr(const char *s, int c);
char	*ft_gnl_strjoin(char *s1, char *s2);
char	*ft_gnl_strtrim_left(char *buffer);
char	*ft_gnl_strtrim_right(char *buffer);

/* Part 6: extra functions */
int		ft_isspace(int c);
int		ft_isquote(int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strcmp_input(const char *input, const char *limiter);
int		ft_fprintf(int fd, const char *string, ...);
int		check_arg_fd(char *string, int *i, va_list args, int fd);
void	ft_free_tabs(void **tab);
int		ft_atoi_base(char *str, char *base);
int		ft_abs(int a);
void	ft_swap(void *a, void *b, size_t size);
char	*ft_str_tolower(char *str);
char	*ft_str_toupper(char *str);
int		ft_checkextension(const char *str, const char *suffix);
char	*ft_strndup(const char *s, size_t n);
int		ft_issquote(int c);
int		ft_isdquote(int c);
char	**ft_tabdup(char **tab);
int		ft_getpid(void);
int		ft_getppid(void);
int		ft_tablen(void **tab);
int		ft_isnumber(char *string);

/* Part 7: extra funcions for Builtins */
char	**ft_str_arr_dup(char **arr);
int		ft_str_arr_len(char **arr);
char	**ft_realloc_str_arr(char **arr, int size);
void	ft_free_str_array(char ***arr);
void	ft_free_str(char **str);
char	*ft_strstrjoin(char *s1, char *s2, char *divider);
char	*ft_append(char **dst, char *src);
void	*ft_free(void **p);
long	ft_atol(const char *str);
bool	ft_issign(char c);
char	*ft_strchr2(const char *s, int c);
char	ft_last_char(const char *string);

#endif