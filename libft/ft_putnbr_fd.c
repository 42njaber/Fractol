/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 18:36:38 by njaber            #+#    #+#             */
/*   Updated: 2017/11/30 02:06:46 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	char			ret[12];
	unsigned int	unb;
	size_t			i;
	size_t			len;

	len = ft_log(nb, 10) + (nb < 0 ? 1 : 0);
	ret[11] = '\0';
	ft_strclr(ret);
	i = 0;
	(nb < 0) && (ret[i] = '-') && ++i;
	unb = (unsigned int)ft_abs(nb);
	while (i < len)
		(ret[i] = '0' + (char)(unb / ft_pow(10, len - i - 1) % 10))
			&& ++i;
	write(fd, ret, len);
}
