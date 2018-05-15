/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 03:43:44 by njaber            #+#    #+#             */
/*   Updated: 2018/01/19 07:10:34 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*str_color(const char *spec, t_buf *buf, int g, va_list arg)
{
	int		i;
	int		color;

	(void)arg;
	i = 0;
	color = 0;
	spec--;
	while (++spec && ((*spec >= '0' && *spec <= '9') || (*spec >= 'A' &&
			*spec <= 'F') || (*spec >= 'a' && *spec <= 'f')) && i++ < 6)
		color = color * 16 + *spec - ('0' * (*spec >= '0' && *spec <= '9') +
			('A' - 10) * (*spec >= 'A' && *spec <= 'F') +
			('a' - 10) * (*spec >= 'a' && *spec <= 'f'));
	str_tobuf(g ? "\e[38;2" : "\e[48;2", 6, buf);
	i = 3;
	while (i-- > 0)
	{
		chr_tobuf(';', 1, buf);
		chr_tobuf('0' + ((color >> (8 * i)) & 0xFF) / 100 % 10, 1, buf);
		chr_tobuf('0' + ((color >> (8 * i)) & 0xFF) / 10 % 10, 1, buf);
		chr_tobuf('0' + ((color >> (8 * i)) & 0xFF) % 10, 1, buf);
	}
	chr_tobuf('m', 1, buf);
	return ((char*)spec);
}

static char		*arg_color(const char *spec, t_buf *buf, int g, va_list arg)
{
	int		i;
	int		color;

	(void)spec;
	color = va_arg(arg, int);
	str_tobuf(g ? "\e[38;2" : "\e[48;2", 6, buf);
	i = 3;
	while (i-- > 0)
	{
		chr_tobuf(';', 1, buf);
		chr_tobuf('0' + ((color >> (8 * i)) & 0xFF) / 100 % 10, 1, buf);
		chr_tobuf('0' + ((color >> (8 * i)) & 0xFF) / 10 % 10, 1, buf);
		chr_tobuf('0' + ((color >> (8 * i)) & 0xFF) % 10, 1, buf);
	}
	chr_tobuf('m', 1, buf);
	return ((char*)spec);
}

static const t_form	g_forms[256] = {
	['0'] = {"\e[0m", "\e[0m", NULL},
	['i'] = {"\e[3m", "\e[3m", NULL},
	['!'] = {"\e[6m", "\e[6m", NULL},
	['u'] = {"\e[4m", "\e[4m", NULL},
	['b'] = {"\e[30m", "\e[40m", NULL},
	['R'] = {"\e[31m", "\e[41m", NULL},
	['G'] = {"\e[32m", "\e[42m", NULL},
	['y'] = {"\e[33m", "\e[43m", NULL},
	['B'] = {"\e[34m", "\e[44m", NULL},
	['m'] = {"\e[35m", "\e[45m", NULL},
	['c'] = {"\e[36m", "\e[46m", NULL},
	['w'] = {"\e[37m", "\e[47m", NULL},
	['@'] = {(char*)1, NULL, arg_color},
	['#'] = {(char*)1, NULL, str_color}
};

char			*pf_format(const char *spec, t_buf *buf, va_list args)
{
	t_form	tmp;
	int		g;

	while (1)
	{
		g = 1;
		if (*spec == ':' && spec++)
			g = 0;
		if ((tmp = g_forms[(int)*spec]).fg != NULL && spec++)
		{
			if (tmp.fg != (char*)1)
				str_tobuf(g ? tmp.fg : tmp.bg,
					ft_strlen(g ? tmp.fg : tmp.bg), buf);
			else
				spec = tmp.f(spec, buf, g, args);
		}
		if (*spec != ',' || !spec++)
			break ;
	}
	if (*spec == '>')
		spec++;
	return ((char*)spec);
}
