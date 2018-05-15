/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:06:46 by njaber            #+#    #+#             */
/*   Updated: 2017/11/30 19:48:34 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *pat, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	strlen;

	strlen = ft_strlen(str);
	len = ft_strlen(pat);
	len = (n > len && strlen > len) ? ft_umin(n, strlen) - len : 0;
	i = 0;
	while (i <= len)
	{
		j = 0;
		while (pat[j] != '\0' && str[i + j] == pat[j] && i + j < n)
			j++;
		if (pat[j] == '\0')
			return ((char*)str + i);
		i++;
	}
	return (NULL);
}
