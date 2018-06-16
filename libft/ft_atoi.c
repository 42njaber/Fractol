/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 12:18:04 by njaber            #+#    #+#             */
/*   Updated: 2018/05/25 21:32:32 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_atoi(const char *str)
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

int				ft_parse_int(const char *str, int *i)
{
	long	ret;
	int		sign;

	ret = 0;
	while (ft_isinvis(str[*i]))
		(*i)++;
	sign = 1;
	(((str[*i] == '-') && (sign = -1) == -1) || (str[*i] == '+'))
		&& (*i)++;
	while (ft_isdigit(str[*i]))
		ret = ret * 10 + (str[(*i)++] - '0');
	return ((int)ret * sign);
}

unsigned int	ft_parse_hex(const char *str, int *i)
{
	unsigned int	ret;
	int				j;
	char			*base;

	base = "0123456789ABCDEF";
	ret = 0;
	while (ft_isinvis(str[*i]))
		(*i)++;
	while (str[*i] != '\0')
	{
		j = 0;
		while (j < 16 && base[j] != str[*i])
			j++;
		if (j == 16)
			break ;
		ret = ret * 16 + j;
		(*i)++;
	}
	return ((unsigned int)ret);
}

double			ft_parse_float(const char *str, int *i)
{
	double	ret;
	double	decim;
	int		sign;

	ret = 0;
	while (ft_isinvis(str[*i]))
		(*i)++;
	sign = 1;
	(((str[*i] == '-') && (sign = -1) == -1) || (str[*i] == '+'))
		&& (*i)++;
	while (ft_isdigit(str[*i]))
		ret = ret * 10 + (str[(*i)++] - '0');
	if (str[*i] == '.')
	{
		(*i)++;
		decim = 10;
		while (ft_isdigit(str[*i]))
		{
			ret += (double)(str[(*i)++] - '0') / decim;
			decim *= 10;
		}
	}
	return (ret * sign);
}
