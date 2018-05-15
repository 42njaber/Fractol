/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:36:04 by njaber            #+#    #+#             */
/*   Updated: 2017/11/30 00:30:18 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	len;

	len = ft_strlen(s1);
	if (n > 0 && ft_strlen(s2) > 0)
		s1[len + ft_umin(ft_strlen(s2), n)] = '\0';
	ft_memccpy(s1 + len, s2, '\0', n);
	return (s1);
}
