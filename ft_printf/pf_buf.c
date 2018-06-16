/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_buf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njaber <neyl.jaber@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 19:29:58 by njaber            #+#    #+#             */
/*   Updated: 2018/05/30 03:01:31 by njaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			flip(t_buf *buf)
{
	t_list	**l_buf;

	l_buf = &(buf->tbuf);
	while (buf->tprinted != 0 && *l_buf != NULL)
	{
		str_tobuf((*l_buf)->content, ft_umin(buf->tprinted, B_SIZE), buf);
		if (buf->tprinted > B_SIZE)
			buf->tprinted -= B_SIZE;
		else
			buf->tprinted = 0;
		l_buf = &((*l_buf)->next);
	}
	buf->tprinted = 0;
	if (buf->tbuf != NULL)
		ft_lstdel(&(buf->tbuf->next), &ft_lstcontdel);
}

void			chr_tobuf(char c, size_t len, t_buf *buf)
{
	while (len > 0)
	{
		ft_memset(buf->buf + buf->printed % B_SIZE, c,
			ft_umin(len, B_SIZE - buf->printed % B_SIZE));
		if (len >= B_SIZE - buf->printed % B_SIZE)
		{
			if (buf->write == 1)
				write(1, buf->buf, B_SIZE);
			else
			{
				if (buf->ret == NULL)
					buf->ret = ft_strldup(buf->buf, B_SIZE);
				else
					buf->ret = ft_strljoin(buf->ret, buf->buf, B_SIZE, 1);
			}
			len -= B_SIZE - buf->printed % B_SIZE;
			buf->printed += B_SIZE - buf->printed % B_SIZE;
		}
		else
		{
			buf->printed += len;
			len = 0;
		}
	}
}

void			chr_totmpbuf(char c, size_t len, t_buf *buf, int prior)
{
	t_list	**l_buf;

	if (prior)
		chr_tobuf(c, len, buf);
	l_buf = &(buf->tbuf);
	while ((*l_buf)->next != NULL)
		l_buf = &((*l_buf)->next);
	while (len > 0 && !prior)
	{
		ft_memset((*l_buf)->content + buf->tprinted % B_SIZE, c,
			ft_umin(len, B_SIZE - buf->tprinted % B_SIZE));
		if (len >= B_SIZE - buf->tprinted % B_SIZE)
		{
			l_buf = &((*l_buf)->next);
			*l_buf = ft_lstnew(NULL, B_SIZE);
			len -= B_SIZE - buf->tprinted % B_SIZE;
			buf->tprinted += B_SIZE - buf->tprinted % B_SIZE;
		}
		else
		{
			buf->tprinted += len;
			len = 0;
		}
	}
}

void			str_tobuf(char *str, size_t len, t_buf *buf)
{
	while (len > 0)
	{
		ft_memcpy(buf->buf + buf->printed % B_SIZE, str,
			ft_umin(len, B_SIZE - buf->printed % B_SIZE));
		if (len >= B_SIZE - buf->printed % B_SIZE)
		{
			if (buf->write == 1)
				write(1, buf->buf, B_SIZE);
			else
			{
				if (buf->ret == NULL)
					buf->ret = ft_strldup(buf->buf, B_SIZE);
				else
					buf->ret = ft_strljoin(buf->ret, buf->buf, B_SIZE, 1);
			}
			str += B_SIZE - buf->printed % B_SIZE;
			len -= B_SIZE - buf->printed % B_SIZE;
			buf->printed += B_SIZE - buf->printed % B_SIZE;
		}
		else
		{
			buf->printed += len;
			len = 0;
		}
	}
}

void			str_totmpbuf(char *str, size_t len, t_buf *buf, int prior)
{
	t_list	**l_buf;

	if (prior)
		str_tobuf(str, len, buf);
	l_buf = &(buf->tbuf);
	while ((*l_buf)->next != NULL)
		l_buf = &((*l_buf)->next);
	while (len > 0 && !prior)
	{
		ft_memcpy((*l_buf)->content + buf->tprinted % B_SIZE, str,
			ft_umin(len, B_SIZE - buf->tprinted % B_SIZE));
		if (len >= B_SIZE - buf->tprinted % B_SIZE)
		{
			l_buf = &((*l_buf)->next);
			*l_buf = ft_lstnew(NULL, B_SIZE);
			str += B_SIZE - buf->tprinted % B_SIZE;
			len -= B_SIZE - buf->tprinted % B_SIZE;
			buf->tprinted += B_SIZE - buf->tprinted % B_SIZE;
		}
		else
		{
			buf->tprinted += len;
			len = 0;
		}
	}
}
