/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 18:09:52 by njaber            #+#    #+#             */
/*   Updated: 2017/11/30 00:40:39 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;

	i = 0;
	if (dst < src)
		while (i++ < len)
			*((unsigned char*)(dst) + i - 1) =
				*((const unsigned char*)(src) + i - 1);
	else
		while (i++ < len)
			*((unsigned char*)(dst) + len - i) =
				*((const unsigned char*)(src) + len - i);
	return (dst);
}
