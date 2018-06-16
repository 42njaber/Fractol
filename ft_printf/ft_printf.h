/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 21:11:55 by njaber            #+#    #+#             */
/*   Updated: 2018/05/30 03:04:43 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <limits.h>
# include <wchar.h>

# define B_SIZE 96

# define BIN "01"
# define OCT "01234567"
# define DEC "0123456789"
# define HEX_MIN "0123456789abcdef"
# define HEX_MAJ "0123456789ABCDEF"

static const	char	*g_base[18] = {
	[2] = BIN,
	[8] = OCT,
	[10] = DEC,
	[16] = HEX_MIN,
	[17] = HEX_MAJ
};

static const	char	g_flags[256] = {
	['#'] = 0x01,
	['0'] = 0x02,
	['-'] = 0x04,
	[' '] = 0x08,
	['+'] = 0x10,
	['\047'] = 0x20
};

typedef struct	s_buf {
	t_list	*tbuf;
	size_t	tprinted;
	size_t	printed;
	char	write;
	char	*ret;
	char	buf[B_SIZE];
}				t_buf;

typedef struct	s_mods {
	char	flags;
	char	cast;
	int		prec;
	size_t	field;
}				t_mods;

typedef struct	s_conv {
	void	(*f)(t_mods, t_byte*, t_buf*, va_list);
	char	flags;
	char	cast;
	t_byte	parm[3];
}				t_conv;

typedef struct	s_form {
	char	*fg;
	char	*bg;
	char	*(*f)(const char *, t_buf*, int g, va_list);
}				t_form;

typedef union	u_int {
	intmax_t	j;
	uintmax_t	u;
}				t_int;

typedef union	u_dbl {
	double			d;
	unsigned long	l;
}				t_dbl;

typedef union	u_ucd {
	char		c[5];
	wint_t		wi;
	wchar_t		wc;
}				t_ucd;

int				ft_printf(const char *format, ...);
char			*ft_printb(const char *format, ...);
void			ft_error(const char *format, ...);
char			*ft_mapper(const char *spec, va_list args, t_buf *buf);
char			*pf_format(const char *parm, t_buf *buf, va_list arg);

wint_t			uctou8(wint_t uc);
double			db_pow(double nb, int pow);
int				db_log(double nb, double log);
double			db_round(double nb, t_mods mods, t_byte *parm);

void			chr_tobuf(char c, size_t len, t_buf *buf);
void			str_tobuf(char *str, size_t len, t_buf *buf);
void			chr_totmpbuf(char c, size_t len, t_buf *buf, int prior);
void			str_totmpbuf(char *str, size_t len, t_buf *buf, int prior);
void			flip(t_buf *buf);

void			pf_str(t_mods mods, t_byte *parm, t_buf *buf, va_list arg);
void			pf_wstr(t_mods mods, t_byte *parm, t_buf *buf, va_list arg);
void			pf_int(t_mods mods, t_byte *parm, t_buf *buf, va_list arg);
void			pf_chr(t_mods mods, t_byte *parm, t_buf *buf, va_list arg);
void			pf_dbl(t_mods mods, t_byte *parm, t_buf *buf, va_list arg);
void			pf_len(t_mods mods, t_byte *parm, t_buf *buf, va_list arg);

#endif
