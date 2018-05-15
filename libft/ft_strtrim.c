/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 13:37:02 by njaber            #+#    #+#             */
/*   Updated: 2017/11/27 21:54:58 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s)
{
	char	*ret;
	size_t	i;
	size_t	j;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (ft_isblank(s[i]) || s[i] == '\n')
		i++;
	j = ft_strlen(s) - 1;
	while (j > i && (ft_isblank(s[j]) || s[j] == '\n'))
		j--;
	j = ft_strlen(s) - j;
	if ((ret = ft_strnew(ft_strlen(s) - j - i + 1)) == NULL)
		return (NULL);
	ft_strncpy(ret, s + i, ft_strlen(s) - j - i + 1);
	ret[ft_strlen(s) - j - i + 1] = '\0';
	return (ret);
}
