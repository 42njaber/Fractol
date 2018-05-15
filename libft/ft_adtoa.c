/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adtoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 23:43:28 by njaber            #+#    #+#             */
/*   Updated: 2017/11/30 02:36:13 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_adtoa(const void *addr)
{
	char	*ret;
	char	*base;
	size_t	i;
	size_t	len;

	base = HEXA;
	len = ft_log(((size_t)addr & 0x00000000ffffffff), 16) +
		((size_t)addr & 0xffffffff00000000 ?
		ft_log(((size_t)addr & 0xffffffff00000000) >> 32, 16) : 0);
	ret = ft_strnew(len);
	i = 0;
	while (i < len)
		(ret[i] = base[((size_t)addr >> 4 * (len - i - 1)) & 0xf]) && i++;
	return (ret);
}
