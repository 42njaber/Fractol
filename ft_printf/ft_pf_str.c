/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 02:24:56 by njaber            #+#    #+#             */
/*   Updated: 2018/01/19 07:09:53 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		to_print(char c, t_buf *buf)
{
	str_totmpbuf("\e[48;47;38m<", 12, buf, 0);
	chr_totmpbuf('0' + (c / 64) % 8, 1, buf, 0);
	chr_totmpbuf('0' + (c / 8) % 8, 1, buf, 0);
	chr_totmpbuf('0' + c % 8, 1, buf, 0);
	str_totmpbuf(">\e[49m", 6, buf, 0);
}

void			pf_str(t_mods mods, t_byte *parm, t_buf *buf, va_list arg)
{
	char	*str;

	if (mods.cast == 'l')
	{
		pf_wstr(mods, parm, buf, arg);
		return ;
	}
	(void)parm;
	str = va_arg(arg, char*);
	if (str == NULL)
		str_totmpbuf("(null)", mods.prec > -1 ? ft_umin(6, mods.prec) : 6,
			buf, 0);
	else if (parm[0])
	{
		while ((mods.prec < 0 && *str != '\0') || mods.prec-- > 0)
			if (!ft_isprint(*str) && (*str != '\0' || mods.prec >= 0))
				to_print(*str++, buf);
			else
				chr_totmpbuf(*str++, 1, buf, 0);
	}
	else
		str_totmpbuf(str, ft_umin(ft_strlen(str), (size_t)mods.prec), buf, 0);
}

static size_t	pf_wstr_len(wint_t *wstr, t_mods mods)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (wstr[j] != L'\0')
	{
		(wstr[j] & 0xffff0000 && (i += 4)) || (wstr[j] & 0xF800 && (i += 3))
		|| (wstr[j] & 0x0780 && (i += 2)) || i++;
		j++;
	}
	return (ft_umin(i, (size_t)mods.prec));
}

void			pf_wstr(t_mods mods, t_byte *parm, t_buf *buf, va_list arg)
{
	size_t	i;
	size_t	j;
	wchar_t	*wstr;
	char	*utf8;
	t_ucd	chr;

	(void)parm;
	wstr = va_arg(arg, wchar_t*);
	str_totmpbuf("(null)", (wstr == NULL) *
		(mods.prec > -1 ? ft_umin(6, mods.prec) : 6), buf, 0);
	if (wstr == NULL)
		return ;
	j = pf_wstr_len((wint_t*)wstr, mods);
	utf8 = ft_strnew(j);
	i = -1;
	chr.c[4] = 0;
	while ((++i == 0 || ft_strlcat(utf8, chr.c, j + 1) < j) && wstr[i] != L'\0')
	{
		chr.wi = uctou8((wint_t)wstr[i]);
		if (ft_strlen(chr.c) + ft_strlcat(utf8, "", j + 1) > j
			&& (j = ft_strlen(utf8)))
			break ;
	}
	str_totmpbuf((char*)utf8, j, buf, 0);
	free(utf8);
}
