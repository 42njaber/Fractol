/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_utility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/25 19:18:10 by njaber            #+#    #+#             */
/*   Updated: 2018/01/18 19:05:29 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

wint_t		uctou8(wint_t uc)
{
	t_ucd	u8;
	char	t;

	u8.wi = 0;
	if (uc < 0x7F)
		u8.wi |= uc & 0x7F;
	else if ((u8.wi |= 0x80 | (0x3F & uc)) && uc <= 0x07FF)
		u8.wi |= 0xC000 | ((uc & 0x07C0) << 2);
	else if ((u8.wi |= 0x8000 | ((uc & 0x0FC0) << 2)) && uc <= 0xFFFF)
		u8.wi |= 0xE00000 | ((uc & 0xF000) << 4);
	else
		u8.wi |= 0xF0800000 | ((uc & 0x03F000) << 4) | ((uc & 0x1C0000) << 6);
	t = u8.c[0];
	u8.c[0] = u8.c[3];
	u8.c[3] = t;
	t = u8.c[1];
	u8.c[1] = u8.c[2];
	u8.c[2] = t;
	while (u8.c[0] == 0 && u8.wi != 0)
		u8.wi = (u8.wi >> 8) & 0xFFFFFF;
	return (u8.wi);
}

double		db_pow(double nb, int i)
{
	double	ret;

	ret = 1;
	if (i > 0)
		while (i-- > 0)
			ret *= nb;
	else
		while (i++ < 0)
			ret /= nb;
	return (ret);
}

int			db_log(double nb, double log)
{
	int		i;

	if (log == 1 || log == 0)
		return (0);
	if (nb < 0)
		nb = -nb;
	i = 0;
	if (nb >= 1)
		while (++i && (nb /= log) > 1)
			;
	else
		while ((--i || 1) && (nb *= log) < log)
			;
	return (i);
}

double		db_round(double nb, t_mods mods, t_byte *parm)
{
	double	e;
	double	ret;
	int		i;
	int		j;

	if (nb == 0)
		return (0);
	ret = nb;
	e = db_pow(10, db_log(nb, 10));
	j = -db_log(e, 10);
	if (nb < 10 || parm[2] == 0 || (parm[2] == 2 && db_log(e, 10) > mods.prec))
		j = -1;
	if (parm[2] == 2)
		j = e > 10 || e < 0.0001 ? 0 : db_log(e, 10) - 1;
	j -= mods.prec;
	while (++j <= 0 && ((e /= 10) || 1))
	{
		i = 10;
		while (i > 0 && e * --i > nb)
			;
		nb -= e * i;
	}
	if (nb > 0.5 * e)
		ret += e;
	return (ret);
}
