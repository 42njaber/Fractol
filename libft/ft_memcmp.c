/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 19:09:33 by njaber            #+#    #+#             */
/*   Updated: 2017/11/29 19:26:41 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (*((const unsigned char*)(s1) + i)
			== *((const unsigned char*)(s2) + i) && i < n - 1)
		i++;
	return (*((const unsigned char*)(s1) + i)
			- *((const unsigned char*)(s2) + i));
}
