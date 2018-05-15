/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 17:24:59 by njaber            #+#    #+#             */
/*   Updated: 2017/11/30 19:44:00 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (i == 0
				|| *((const unsigned char*)src + i - 1) != (unsigned char)c))
		((*((unsigned char*)dst + i) =
			*((const unsigned char*)src + i)) || 1) && i++;
	if (i != 0 && *((const unsigned char*)src + i - 1) == (unsigned char)c)
		return ((void*)((char*)dst + i));
	return (NULL);
}
