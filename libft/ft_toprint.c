/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 17:26:40 by njaber            #+#    #+#             */
/*   Updated: 2017/11/30 00:35:51 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char *g_map[256] = {
	[0] = "\\0",
	[1] = "SOH",
	[2] = "STX",
	[3] = "ETX",
	[4] = "EOT",
	[5] = "ENQ",
	[6] = "ACK",
	[7] = "\\a",
	[8] = "\\b",
	[9] = "\\t",
	[10] = "\\n",
	[11] = "\\v",
	[12] = "\\r",
	[13] = "SO",
	[14] = "SI",
	[15] = "DLE",
	[16] = "DC1",
	[17] = "DC2",
	[18] = "DC3",
	[19] = "DC4",
	[20] = "NACK",
	[21] = "SYNC",
	[22] = "ETB",
	[23] = "CAN",
	[24] = "EM",
	[25] = "SUB",
	[26] = "ESC",
	[27] = "FS",
	[28] = "GS",
	[29] = "RS",
	[30] = "US",
	[127] = "DEL"
};

char	*ft_toprint(int c)
{
	char	*ret;

	if (ft_isprint(c))
	{
		ret = ft_strnew(4);
		ret[0] = '\'';
		ret[1] = (char)c;
		ret[2] = '\'';
		ret[3] = ' ';
	}
	else if (c < -128 || c > 127)
		ret = ft_strdup("UnKn");
	else if (!ft_isascii(c))
		ret = ft_strdup("UniCd");
	else
		ret = ft_strdup(g_map[c]);
	return (ret);
}
