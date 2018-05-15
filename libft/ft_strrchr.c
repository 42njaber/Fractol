/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:56:37 by njaber            #+#    #+#             */
/*   Updated: 2017/11/23 21:02:14 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ret;
	char	*tmp;

	ret = NULL;
	tmp = ft_memchr(s, c, ft_strlen(s) + 1);
	while (tmp != NULL)
	{
		ret = tmp;
		tmp = ft_memchr(tmp + 1, c, ft_strlen(tmp));
	}
	return (ret);
}
