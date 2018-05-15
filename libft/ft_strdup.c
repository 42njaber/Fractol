/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:15:35 by njaber            #+#    #+#             */
/*   Updated: 2017/11/29 23:58:47 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*ret;

	if ((ret = ft_strnew(ft_strlen(s))) == NULL)
		return (NULL);
	i = 0;
	while ((ret[i] = s[i]) != 0 && ++i)
		;
	return (ret);
}
