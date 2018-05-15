/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 22:01:46 by njaber            #+#    #+#             */
/*   Updated: 2017/11/30 01:50:41 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const size_t						g_typesize[16] = {
	[(t_type)CHAR] = sizeof(char),
	[(t_type)UCHAR] = sizeof(unsigned char),
	[(t_type)INT] = sizeof(int),
	[(t_type)UINT]= sizeof(unsigned int),
	[(t_type)LONG] = sizeof(long),
	[(t_type)ULONG] = sizeof(unsigned long),
	[(t_type)LLONG] = sizeof(long long),
	[(t_type)ULLONG] = sizeof(unsigned long long),
	[(t_type)PTR] = sizeof(void*)
};

static void		ft_tostr(const void *data, char *buf, t_type type)
{
	char *tmp;

	if (type == CHAR)
		tmp = ft_toprint(*(const char*)data);
	else if (type == INT)
		tmp = ft_itoa(*(const int*)data);
	else if (type == PTR)
		tmp = ft_adtoa(*(void**)data);
	else
		tmp = ft_strdup("Not supported");
	ft_strncpy(buf, tmp, 60);
	free(tmp);
}

static void		ft_data_print(const void *data, t_type type)
{
	char	tmp[60];
	char	str[56];
	size_t	len;
	size_t	tmp_len;

	len = g_typesize[type] * 7 - 1;
	ft_memset((void*)str, ' ', len);
	ft_tostr(data, tmp, type);
	tmp_len = ft_strlen(tmp);
	write(1, str, (tmp_len > len ? 0 : len - tmp_len));
	write(1, tmp, (tmp_len > len ? len : tmp_len));
}

static void		ft_putbytes(const void *addr, size_t len, size_t type_l)
{
	size_t	i;
	char	*base;

	base = HEXA;
	i = 0;
	while (i < len)
	{
		if (i % type_l == 0)
			ft_putstr(CL_RED" | "CL_WHITE);
		else
			ft_putchar(' ');
		ft_putchar(base[(*((const t_byte*)addr + i) & 0xf0) >> 4]);
		ft_putchar(base[*((const t_byte*)addr + i) & 0xf]);
		ft_putstr(":");
		ft_putchar((*((const t_byte*)addr + i) / 100u) % 10u + '0');
		ft_putchar((*((const t_byte*)addr + i) / 10u) % 10u + '0');
		ft_putchar(*((const t_byte*)addr + i) % 10u + '0');
		i++;
	}
	ft_putstr(CL_RED" |"CL_WHITE);
}

void			ft_print_memory(const void *addr, size_t len, t_type type)
{
	size_t	i;
	char	*tmp;

	if (addr == NULL)
		ft_putstr("("CL_RED"NULL"CL_WHITE")\n");
	(addr != NULL) && (len += 8) && (addr = (const char*)(addr) - 8);
	while (len > 8 && addr != NULL && (len -= 8)
			&& (addr = (const char*)(addr) + 8))
	{
		tmp = ft_adtoa(addr);
		ft_putstr(tmp);
		ft_putstr(":");
		ft_putbytes(addr, ft_umin(len, 8), g_typesize[type]);
		write(1, CL_RED"\n____________________________"CL_WHITE,
				ft_strlen(tmp) + 7);
		free(tmp);
		i = 0;
		while (i * g_typesize[type] < ft_umin(len, 8))
		{
			ft_putstr(CL_RED"_|_"CL_WHITE);
			ft_data_print((const void*)
						((const char*)addr + i++ * g_typesize[type]), type);
		}
		ft_putstr(CL_RED"_|"CL_WHITE"\n");
	}
}
