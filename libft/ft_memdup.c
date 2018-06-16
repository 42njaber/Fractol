/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 02:22:08 by njaber            #+#    #+#             */
/*   Updated: 2018/05/30 03:21:24 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memdup(const void *mem, size_t len)
{
	void	*ret;

	if ((ret = (void*)ft_memalloc(len)) == NULL)
		return (NULL);
	ft_memcpy(ret, mem, len);
	return (ret);
}

char	*ft_strldup(const char *mem, size_t len)
{
	char	*ret;

	len = ft_min(len, ft_strlen(mem));
	ret = 0;
	if ((ret = (char*)ft_memalloc(len + 1)) == NULL)
		return (NULL);
	ft_memcpy(ret, mem, len);
	ret[len] = 0;
	return (ret);
}

char	*ft_strljoin(char *mem1, char *mem2, size_t len2, int del)
{
	char	*ret;
	size_t	len1;

	len1 = ft_strlen(mem1);
	len2 = ft_min(len2, ft_strlen(mem2));
	if ((ret = (char*)ft_memalloc(len1 + len2 + 1)) == NULL)
		return (NULL);
	ft_memcpy(ret, mem1, len1);
	ft_memcpy(ret + len1, mem2, len2);
	ret[len1 + len2] = 0;
	if (del % 2 == 1)
		free(mem1);
	if (del > 1)
		free(mem2);
	return (ret);
}
