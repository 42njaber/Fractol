/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 06:29:58 by njaber            #+#    #+#             */
/*   Updated: 2018/01/19 01:41:46 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_int	read_arg(va_list arg, char cast, int uns)
{
	t_int		ret;

	if (cast == -'h')
		((uns) && ((ret.u = (unsigned char)va_arg(arg, unsigned int)) || 1))
			|| (ret.j = (char)va_arg(arg, int));
	if (cast == 'h')
		((uns) && ((ret.u = (unsigned short)va_arg(arg, unsigned int)) || 1))
			|| (ret.j = (short)va_arg(arg, int));
	if (cast == 0)
		((uns) && ((ret.u = va_arg(arg, unsigned int)) || 1))
			|| (ret.j = va_arg(arg, int));
	if (cast == 'l')
		((uns) && ((ret.u = va_arg(arg, unsigned long)) || 1))
			|| (ret.j = va_arg(arg, long));
	if (cast == -'l')
		((uns) && ((ret.u = va_arg(arg, unsigned long long)) || 1))
			|| (ret.j = va_arg(arg, long long));
	if (cast == 'j')
		((uns) && ((ret.u = va_arg(arg, uintmax_t)) || 1))
			|| (ret.j = va_arg(arg, intmax_t));
	if (cast == 'z')
		((uns) && ((ret.u = va_arg(arg, size_t)) || 1))
			|| (ret.j = va_arg(arg, size_t));
	return (ret);
}

static void		pf_int2(t_int i, t_mods mods, t_byte *parm, t_buf *buf)
{
	uintmax_t	j;
	const char	*base;

	base = g_base[parm[0] + (parm[0] == 16) * parm[2]];
	j = 1;
	while (j < UINTMAX_MAX / parm[0] && i.u / j >= parm[0])
		j *= parm[0];
	while (mods.prec-- > (int)ft_log(j, parm[0]))
	{
		chr_totmpbuf('0', 1, buf, 0);
		if (mods.flags & g_flags['\047'] && parm[0] == 10 && mods.prec % 3 == 0)
			chr_totmpbuf(' ', 1, buf, 0);
	}
	while (j >= 1 && (i.u != 0 || mods.prec != -1 || (parm[0] == 8 &&
		g_flags['#'] & mods.flags)))
	{
		if (mods.flags & g_flags['\047'] && (ft_ulog(j, 10)) % 3 == 0
			&& i.u / j > parm[0])
			chr_totmpbuf(' ', 1, buf, 0);
		chr_totmpbuf(base[(i.u / j) % parm[0]], 1, buf, 0);
		j /= parm[0];
	}
}

void			pf_int(t_mods mods, t_byte *parm, t_buf *buf, va_list arg)
{
	t_int	i;

	i = read_arg(arg, mods.cast, parm[1] == 1);
	if (parm[1] == 0)
	{
		if (i.j < 0 && (i.u = -i.j))
			chr_totmpbuf('-', 1, buf, (g_flags['0'] & mods.flags
				&& mods.prec < 0));
		else if (mods.flags & (g_flags[' '] | g_flags['+']))
			chr_totmpbuf(mods.flags & g_flags['+'] ? '+' : ' ', 1, buf,
				(g_flags['0'] & mods.flags && mods.prec < 0));
	}
	else if ((mods.flags & (g_flags['#']) && i.u != 0) || mods.flags & 0x80)
	{
		if (parm[0] == 8 && (mods.prec-- || 1))
			chr_totmpbuf('0', 1, buf, 0);
		else if (parm[0] == 16)
			str_totmpbuf(parm[2] ? "0X" : "0x", 2, buf,
				(g_flags['0'] & mods.flags && mods.prec < 0));
	}
	pf_int2(i, mods, parm, buf);
}
