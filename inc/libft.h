/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 16:20:23 by njaber            #+#    #+#             */
/*   Updated: 2018/03/15 12:33:13 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>

typedef unsigned char	t_byte;

void			ft_bzero(void *s, size_t n);
void			*ft_memalloc(size_t size);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			ft_memdel(void **ap);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_realloc(void **mem, size_t p_size, size_t n_size);

char			*ft_adtoa(const void *addr);
int				ft_atoi(const char *str);
char			*ft_bitstoa(t_byte byte);
char			*ft_itoa(int n);
char			*ft_strcat(char *s1, const char *s2);
void			ft_strclr(char *s);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strchr(const char *s, int c);
char			*ft_strcpy(char *dst, const char *src);
void			ft_strdel(char **as);
char			*ft_strdup(const char *s);
int				ft_strequ(const char *s1, const char *s2);
void			ft_striter(char *s, void (*f)(char*));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strjoin(const char *s1, const char *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *str);
char			*ft_strmap(const char *s, char (*f)(char));
char			*ft_strmapi(const char *s, char (*f)(unsigned int, char));
char			*ft_strncat(char *s1, const char *s2, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strncpy(char *dst, const char *src, size_t len);
int				ft_strnequ(const char *s1, const char *s2, size_t n);
char			*ft_strnew(size_t size);
char			*ft_strnstr(const char *str, const char *pat, size_t n);
char			*ft_strrchr(const char *s, int c);
char			**ft_strsplit(const char *s, char c);
char			*ft_strstr(const char *str, const char *pat);
char			*ft_strsub(const char *s, unsigned int start, size_t len);
char			*ft_strtrim(const char *s);

int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isblank(int c);
int				ft_isdigit(int c);
int				ft_isinvis(int c);
int				ft_islower(int c);
int				ft_isprint(int c);
int				ft_isupper(int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*ft_toprint(int c);

# define CL_RED		"\x1b[31m"
# define CL_GREEN	"\x1b[32m"
# define CL_YELLOW	"\x1b[33m"
# define CL_BLUE	"\x1b[34m"
# define CL_MAGENTA	"\x1b[35m"
# define CL_CYAN	"\x1b[36m"
# define CL_WHITE	"\x1b[0m"

# define HEXA		"0123456789abcdef"

typedef enum	e_type {
	CHAR,
	WCHAR,
	UCHAR,
	INT,
	UINT,
	LONG,
	ULONG,
	LLONG,
	ULLONG,
	DOUBLE,
	FLOAT,
	PTR
}				t_type;

void			ft_print_memory(const void *addr, size_t len, t_type type);
void			ft_print_bits(const t_byte *bytes, size_t len);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl(const char *str);
void			ft_putendl_fd(const char *str, int fd);
void			ft_putnbr(int nb);
void			ft_putnbr_fd(int nb, int fd);
void			ft_putstr(const char *str);
void			ft_putstr_fd(const char *str, int fd);

# ifndef LONG_MAX
#  define LONG_MAX	9223372036854775807L
# endif
# ifndef INT_MAX
#  define INT_MAX	2147483647
# endif

size_t			ft_abs(long n);
long			ft_max(long n1, long n2);
long			ft_min(long n1, long n2);
size_t			ft_umax(size_t n1, size_t n2);
size_t			ft_umin(size_t n1, size_t n2);
size_t			ft_log(long n, long base);
size_t			ft_ulog(uintmax_t n, uintmax_t base);
size_t			ft_pow(size_t nb, size_t exp);

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

void			ft_lstadd(t_list **alst, t_list *newlst);
void			ft_lstcontdel(void *cont, size_t cont_len);
void			ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstiter(t_list *lst, void (*f)(t_list*));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list*));
t_list			*ft_lstnew(const void *content, size_t content_size);

#endif
