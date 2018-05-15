/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 22:39:15 by njaber            #+#    #+#             */
/*   Updated: 2018/01/19 06:39:38 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_len(t_mods mods, t_byte *parm, t_buf *buf, va_list arg)
{
	void	*var;

	(void)parm;
	var = va_arg(arg, void*);
	if (mods.cast == -'h')
		*((char*)var) = (char)buf->printed;
	if (mods.cast == 'h')
		*((short*)var) = (short)buf->printed;
	if (mods.cast == 0)
		*((int*)var) = (int)buf->printed;
	if (mods.cast == -'h')
		*((long*)var) = (long)buf->printed;
	if (mods.cast == -'h')
		*((long long*)var) = (long)buf->printed;
	if (mods.cast == -'h')
		*((intmax_t*)var) = (intmax_t)buf->printed;
	if (mods.cast == -'h')
		*((size_t*)var) = (size_t)buf->printed;
}
