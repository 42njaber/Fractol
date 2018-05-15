/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 18:11:32 by njaber            #+#    #+#             */
/*   Updated: 2017/11/30 02:06:56 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char			*ret;
	unsigned int	unb;
	size_t			i;
	size_t			len;

	len = ft_log(n, 10) + (n < 0);
	if ((ret = ft_strnew(len)) == NULL)
		return (NULL);
	i = 0;
	((n < 0) && (ret[i++] = '-')
	&& (unb = (unsigned int)-n))
		|| (unb = (unsigned int)n);
	while (i < len)
		(ret[i] = '0' + (char)ft_abs((n / (int)ft_pow(10, len - i - 1) % 10)))
			&& ++i;
	ret[len] = '\0';
	return (ret);
}
