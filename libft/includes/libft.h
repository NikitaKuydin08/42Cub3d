/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkuydin <nkuydin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:23:14 by nkuydin           #+#    #+#             */
/*   Updated: 2025/12/08 21:22:14 by nkuydin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <stdarg.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

int			ft_isalpha(int c);
size_t		ft_strlen(const char *src);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
char		*ft_strdup(const char *src);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memset(void *src, int c, unsigned int n);
void		ft_bzero(void *str, unsigned int n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, void *src, unsigned int n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strchr(const char *str, int chr);
char		*ft_strrchr(const char *str, int chr);
void		*ft_memchr(const void *str, int chr, size_t n);
char		*ft_strnstr(const char *src, const char *to_find, size_t len);
int			ft_toupper(int chr);
int			ft_tolower(int c);
void		*ft_calloc(size_t data, size_t size);
char		*ft_realloc(char *ptr, size_t size);
char		*ft_substr(const char *str, unsigned int start, size_t len);
char		*ft_strjoin(const char *s1, const char *s2);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(const char *str, int fd);
void		ft_putendl_fd(char *str, int fd);
void		ft_putnbr_fd(int n, int fd);
char		*ft_itoa(int n);
char		*ft_strmapi(const char *str, char (*f)(unsigned int, char));
void		ft_striteri(char *str, void (*f)(unsigned int, char*));
char		*ft_strtrim(const char *str, char const *set);
char		**ft_split(const char *str, char c);

// ft_printf
int			ft_printstr(char *str);
int			ft_print_unsigned(unsigned int nb);
int			ft_printhex(unsigned int hex, int c);
int			ft_printint(int nb);
int			ft_printptr(unsigned long long ptr);

// gnl
char		*ft_get_line(char *storage);
char		*ft_read_file(int fd, char *buff);
void		ft_update_storage(char **storage);
char		*ft_free(char *storage);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif