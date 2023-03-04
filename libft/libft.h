/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouly <amouly@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:14:58 by llion             #+#    #+#             */
/*   Updated: 2023/03/04 13:31:53 by amouly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 7
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct g_list
{
	char			*content;
	struct g_list	*next;
}					t_gnl_list;

/*  --------- PARTIE 1 ---------  */

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *b, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_atoi(const char *str);

void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);

/*  --------- PARTIE 2 ---------  */

char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
void 		split_and_print(char *line);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

/*  --------- BONUS ---------  */

t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *newly);
int			ft_lstsize(t_list *lst);	
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *newly);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/*  --------- PRINTF ---------  */

int			ft_printf(const char *input, ...);
int			ft_printnbr(int n, int fd);
int			ft_printchar(char c, int fd);
int			ft_printstr(char *str, int fd);
int			ft_printuint(unsigned int n, int fd);
int			ft_printx_min(unsigned int n, int fd);
int			ft_printx(unsigned int n, int fd);
int			ft_printp(unsigned long long int p, int fd);
int			ft_printpct(int fd);
int			ft_numlen(unsigned int n);

/*  --------- GET_NEXT_LINE ---------  */

char		*get_next_line(int fd);
void		read_and_fill_tank(t_gnl_list **tank, int fd);
char		*extract_and_fill_line(t_gnl_list *tank);
void		malloc_line(t_gnl_list *tank, char **line);
void		clean_tank(t_gnl_list **tank);

int			find_new_line(t_gnl_list *node);
void		ft_lst_add_back(t_gnl_list **lst, int lu, char *buff);
void		free_tank(t_gnl_list *tank, int index);
int			len(char *str);
t_gnl_list	*ft_lstlast_gnl(t_gnl_list *tank);

#endif
