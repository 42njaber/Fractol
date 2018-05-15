/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bitstoa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 02:24:48 by njaber            #+#    #+#             */
/*   Updated: 2017/11/30 02:32:02 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_bitstoa(const t_byte byte)
{
	char	*ret;
	size_t	i;

	if ((ret = ft_strnew(sizeof(char) * 8)) == NULL)
		return (NULL);
	i = 0;
	while (i < 8)
		(ret[i] = '0' + ((byte & 0x80 >> i) != 0)) && i++;
	return (ret);
}
