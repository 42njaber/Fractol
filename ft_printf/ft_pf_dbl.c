/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_dbl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 18:08:23 by njaber            #+#    #+#             */
/*   Updated: 2018/01/19 12:25:07 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	put_fract_hex(t_dbl d, t_mods mods, t_byte *parm, t_buf *buf)
{
	const char		*base;
	size_t			fract;
	size_t			exp;

	str_totmpbuf(parm[1] ? "0X" : "0x", 2, buf, 0);
	exp = 0;
	fract = (d.l & 0x000fffffffffffff) << 12;
	base = g_base[16 + parm[1]];
	if (d.d != 0)
		chr_totmpbuf((mods.prec == 0 && ((fract >> 56) & 0xff) > 0x80)
			? '2' : '1', 1, buf, 0);
	else
		chr_totmpbuf('0', 1, buf, 0);
	if (mods.prec != 0)
		chr_totmpbuf('.', 1, buf, 0);
	fract += (unsigned long)(mods.prec > 0 && ((fract >> (56 - mods.prec * 4))
		& 0xFF) > 0x80) << (64 - mods.prec * 4);
	while ((mods.prec < 0 && fract != 0) || mods.prec-- > 0)
	{
		chr_totmpbuf(base[((fract >> 60) & 0xF)], 1, buf, 0);
		fract <<= 4;
	}
}

static void	put_fract_dec(t_dbl d, t_mods mods, t_byte *parm, t_buf *buf)
{
	int		i;
	int		digit;
	int		j;
	double	e;

	e = 10;
	while (d.d >= e && ((digit = -db_log(e * 10, 10)) || 1))
		e *= 10;
	if (d.d != 0 && (parm[2] == 0 || (parm[2] == 2 && d.d < 0.00001)))
		while (d.d < e / 10)
			e /= 10;
	if (d.d < 10 || parm[2] == 0 || (parm[2] == 2 && db_log(e, 10) > mods.prec))
		digit = -1;
	if ((j = digit - mods.prec) <= digit && parm[2] == 2)
		j = (e > 10 || e < 0.0001 ? 0 : db_log(e, 10) - 1) - mods.prec;
	while (j++ < 0 && (parm[2] != 2 || digit < 0 || d.d > db_pow(10, j - 1) * e)
		&& (i = 10) == 10 && (e /= 10) > 0)
	{
		while (i > 0 && (--i * e) > d.d)
			;
		chr_totmpbuf('.', digit++ == 0 && j != mods.prec, buf, 0);
		chr_totmpbuf('0' + i, ((d.d -= e * i) == 0 || 1), buf, 0);
		if (mods.flags & g_flags['\047'] && digit < 0 && -digit % 3 == 0)
			chr_totmpbuf(' ', 1, buf, 0);
	}
}

static void	put_exp(double d, char base, t_byte *parm, t_buf *buf)
{
	size_t			i;
	size_t			j;
	double			k;

	chr_totmpbuf(((base == 2) ? 'p' : 'e') - (parm[1] * 32), 1, buf, 0);
	chr_totmpbuf((d < 1 && d != 0) ? '-' : '+', 1, buf, 0);
	i = 0;
	if (d >= 1)
	{
		k = 1.0 / base;
		while ((k *= base) < d / base)
			i++;
	}
	else if (d != 0)
	{
		k = 1.0 * base;
		while ((k /= base) > d)
			i++;
	}
	j = (base == 10) ? 10 : 1;
	while (j * 10 < i)
		j *= 10;
	chr_totmpbuf('0' + (i / j) % 10, 1, buf, 0);
	while ((j /= 10) > 0)
		chr_totmpbuf('0' + (i / j) % 10, 1, buf, 0);
}

void		pf_dbl(t_mods mods, t_byte *parm, t_buf *buf, va_list arg)
{
	t_dbl	nb;

	nb.d = va_arg(arg, double);
	if (((nb.l >> 52) & 0x7FF) == 0x7FF &&
		mods.field > 3 + (nb.l == (0xFFFul << 52)))
		chr_totmpbuf(' ', mods.field - 3 + (nb.l == (0xFFFul << 52)), buf, 1);
	if (((nb.l >> 52) & 0x7FF) == 0x7FF && nb.l << 12)
		str_totmpbuf(parm[1] ? "NAN" : "nan", 3, buf, 0);
	else if (((nb.l >> 52) & 0x7FF) == 0x7FF && (nb.l >> 60) == 0x8)
		str_totmpbuf(parm[1] ? "-INF" : "-inf", 4, buf, 0);
	else if (((nb.l >> 52) & 0x7FF) == 0x7FF)
		str_totmpbuf(parm[1] ? "INF" : "inf", 3, buf, 0);
	if (((nb.l >> 52) & 0x7FF) == 0x7FF)
		return ;
	if (nb.l & (0x8l << 60) && ((nb.d = -nb.d) || 1))
		chr_totmpbuf('-', 1, buf, (g_flags['0'] & mods.flags));
	mods.prec == -1 && parm[0] != 16 && (mods.prec = 6);
	(parm[0] != 16) && (nb.d = db_round(nb.d, mods, parm));
	if (parm[0] == 16)
		put_fract_hex(nb, mods, parm, buf);
	else
		put_fract_dec(nb, mods, parm, buf);
	if (parm[2] == 0 || (parm[2] == 2 && nb.d != 0 &&
		(nb.d > db_pow(10, mods.prec) || nb.d < 0.00001)))
		put_exp(nb.d, parm[0] == 16 ? 2 : 10, parm, buf);
}
