/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_chr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 13:03:22 by njaber            #+#    #+#             */
/*   Updated: 2018/01/19 11:24:43 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			pf_chr(t_mods mods, t_byte *parm, t_buf *buf, va_list arg)
{
	t_ucd	c8;

	(void)parm;
	if (mods.cast == 'l')
	{
		c8.wi = va_arg(arg, wint_t);
		c8.wi = uctou8(c8.wi);
		c8.c[4] = 0;
		str_totmpbuf(c8.c, ft_umax(ft_strlen(c8.c), 1), buf, 0);
	}
	else
	{
		c8.c[0] = (char)va_arg(arg, int);
		chr_totmpbuf(c8.c[0], 1, buf, 0);
	}
}
