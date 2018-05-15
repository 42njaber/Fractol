/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:05:31 by njaber            #+#    #+#             */
/*   Updated: 2017/11/30 19:11:37 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *pat)
{
	size_t	i;
	size_t	j;
	size_t	len;

	len = ft_strlen(str);
	len = len - ft_umin(len, ft_strlen(pat));
	i = 0;
	while (i <= len)
	{
		j = 0;
		while (pat[j] != '\0' && str[i + j] == pat[j])
			j++;
		if (pat[j] == '\0')
			return ((char*)str + i);
		i++;
	}
	return (NULL);
}
