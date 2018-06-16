/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 21:57:49 by njaber            #+#    #+#             */
/*   Updated: 2018/05/30 02:58:13 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char	g_cast[256] = {
	['h'] = 'h',
	['l'] = 'l',
	['j'] = 1,
	['z'] = 1,
	['L'] = 1
};

static const int	g_nbr[256] = {
	['d'] = 1,
	['D'] = 1,
	['i'] = 1,
	['o'] = 1,
	['O'] = 1,
	['u'] = 1,
	['U'] = 1,
	['x'] = 1,
	['X'] = 1,
	['p'] = 1
};

static const t_conv	g_conv[256] = {
	['s'] = {pf_str, 0, 0, {0}},
	['r'] = {pf_str, 0, 0, {1}},
	['S'] = {pf_wstr, 0, 0, {0}},
	['c'] = {pf_chr, 0, 0, {0}},
	['C'] = {pf_chr, 0, 'l', {0}},
	['b'] = {pf_int, 0, 0, {2, 1}},
	['d'] = {pf_int, 0, 0, {10, 0}},
	['D'] = {pf_int, 0, 'l', {10, 0}},
	['i'] = {pf_int, 0, 0, {10, 0}},
	['o'] = {pf_int, 0, 0, {8, 1}},
	['O'] = {pf_int, 0, 'l', {8, 1}},
	['u'] = {pf_int, 0, 0, {10, 1}},
	['U'] = {pf_int, 0, 'l', {10, 1}},
	['x'] = {pf_int, 0, 0, {16, 1, 0}},
	['X'] = {pf_int, 0, 0, {16, 1, 1}},
	['p'] = {pf_int, 0x80, 'z', {16, 1, 0}},
	['a'] = {pf_dbl, 0, 0, {16, 0, 0}},
	['A'] = {pf_dbl, 0, 0, {16, 1, 0}},
	['e'] = {pf_dbl, 0, 0, {10, 0, 0}},
	['E'] = {pf_dbl, 0, 0, {10, 1, 0}},
	['f'] = {pf_dbl, 0, 0, {10, 0, 1}},
	['F'] = {pf_dbl, 0, 0, {10, 1, 1}},
	['g'] = {pf_dbl, 0, 0, {10, 0, 2}},
	['G'] = {pf_dbl, 0, 0, {10, 1, 2}},
	['n'] = {pf_len, 0x40, 0, {0}}
};

static void			ft_mapper2(char c, t_mods mods, va_list arg, t_buf *buf)
{
	t_conv	conv;
	size_t	i;

	conv = g_conv[(int)c];
	if (conv.cast)
		mods.cast = conv.cast;
	mods.flags |= conv.flags;
	if (conv.f)
	{
		i = buf->printed;
		buf->tprinted = 0;
		conv.f(mods, conv.parm, buf, arg);
		i = buf->printed - i + buf->tprinted;
	}
	else
		i = 1;
	if (!(mods.flags & (g_flags['-'] | 0x40)) && mods.field > i)
		chr_tobuf(mods.flags & g_flags['0'] && (mods.prec < 0 || !g_nbr[(int)c])
			? '0' : ' ', mods.field - i, buf);
	if (conv.f)
		flip(buf);
	else
		chr_tobuf(c, 1, buf);
	if ((mods.flags & g_flags['-']) && !(mods.flags & 0x40) && mods.field > i)
		chr_tobuf(' ', mods.field - i, buf);
}

static void			pf_atoi(char **format, va_list args, t_mods *mods)
{
	int		ret;
	int		mod;

	mod = 0;
	if (**format == '.' && (mod = 1))
		(*format)++;
	ret = 0;
	if (**format == '*' && (*format)++)
	{
		ret = va_arg(args, int);
		if (*(*format - 2) != '.' && ret < 0 && ((ret = -ret) || 1))
			mods->flags |= g_flags['-'];
		else if (ret < 0 && (ret = -1))
			;
	}
	else
		while (ft_isdigit(**format))
			ret = ret * 10 + *((*format)++) - '0';
	if (mod == 1)
		mods->prec = ret;
	else
		mods->field = ret;
}

char				*ft_mapper(const char *spec, va_list args, t_buf *buf)
{
	t_mods	mods;

	if (*spec == '<')
		return (pf_format(spec + 1, buf, args));
	mods = (t_mods){0, 0, -1, 0};
	while (*spec)
	{
		if (g_flags[(int)*spec] != 0)
			mods.flags |= g_flags[(int)*(spec++)];
		else if ((*spec >= '1' && *spec <= '9') || *spec == '*' || *spec == '.')
			pf_atoi((char**)&spec, args, &mods);
		else if (g_cast[(int)*spec])
			mods.cast = *(++spec) != 1 && *spec == g_cast[(int)*(spec - 1)] &&
				spec++ ? -*(spec - 2) : *(spec - 1);
		else
			break ;
	}
	if (*spec)
		ft_mapper2(*(spec++), mods, args, buf);
	return ((char*)spec);
}
