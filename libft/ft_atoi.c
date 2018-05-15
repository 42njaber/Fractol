/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:18:04 by njaber            #+#    #+#             */
/*   Updated: 2017/11/29 21:28:33 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long	ret;
	int		sign;

	ret = 0;
	while (ft_isinvis(*str))
		str++;
	sign = 1;
	(((*str == '-') && (sign = -1) == -1) || (*str == '+'))
		&& str++;
	while (ft_isdigit(*str))
		ret = ret * 10 + (*(str++) - '0');
	return ((int)ret * sign);
}
